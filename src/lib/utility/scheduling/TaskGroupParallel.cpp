// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TaskGroupParallel.hpp"

#include <chrono>
#include <thread>

#include "ScopedFunctor.hpp"
#include "TaskRunner.hpp"

constexpr int64_t SleepTimeInMS = 25;

struct TaskGroupParallel::TaskInfo final {
  explicit TaskInfo(std::shared_ptr<TaskRunner> taskRunner) : taskRunner(std::move(taskRunner)) {}

  std::shared_ptr<TaskRunner> taskRunner;
  std::shared_ptr<std::thread> thread;
  volatile bool active = false;
};

TaskGroupParallel::TaskGroupParallel() = default;

TaskGroupParallel::~TaskGroupParallel() = default;

void TaskGroupParallel::addTask(std::shared_ptr<Task> task) {
  m_tasks.push_back(std::make_shared<TaskInfo>(std::make_shared<TaskRunner>(task)));
}

void TaskGroupParallel::doEnter(std::shared_ptr<Blackboard> blackboard) {
  m_taskFailed = false;

  if (m_needsToStartThreads) {
    m_needsToStartThreads = false;
    m_activeTaskCount = static_cast<int>(m_tasks.size());
    for (auto & m_task : m_tasks) {
      m_task->active = true;
      m_task->thread = std::make_shared<std::thread>(&TaskGroupParallel::processTaskThreaded, this, m_task,
                                                     blackboard, m_activeTaskCountMutex);
    }
  }
}

Task::TaskState TaskGroupParallel::doUpdate([[maybe_unused]] std::shared_ptr<Blackboard> blackboard) {
  std::this_thread::sleep_for(std::chrono::milliseconds(SleepTimeInMS));

  if (m_tasks.empty() && getActiveTaskCount() > 0) {
    return STATE_RUNNING;
  }

  return (m_taskFailed ? STATE_FAILURE : STATE_SUCCESS);
}

void TaskGroupParallel::doExit([[maybe_unused]] std::shared_ptr<Blackboard> blackboard) {
  for (auto & m_task : m_tasks) {
    m_task->thread->join();
    m_task->thread.reset();
  }
}

void TaskGroupParallel::doReset(std::shared_ptr<Blackboard> blackboard) {
  for (auto & m_task : m_tasks) {
    m_task->taskRunner->reset();
    if (!m_task->active) {
      {
        std::lock_guard<std::mutex> lock(*m_activeTaskCountMutex);
        ++m_activeTaskCount;
      }
      m_task->thread->join();
      m_task->active = true;
      m_task->thread = std::make_shared<std::thread>(&TaskGroupParallel::processTaskThreaded, this, m_task,
                                                         blackboard, m_activeTaskCountMutex);
    }
  }
}

void TaskGroupParallel::doTerminate() {
  for (auto & m_task : m_tasks) {
    m_task->taskRunner->terminate();
  }

  for (auto & m_task : m_tasks) {
    if (m_task->thread) {
      m_task->thread->join();
      m_task->thread.reset();
    }
  }
}

void TaskGroupParallel::processTaskThreaded(const std::shared_ptr<TaskInfo>& taskInfo, std::shared_ptr<Blackboard> blackboard,
                                            const std::shared_ptr<std::mutex>& activeTaskCountMutex) {
  ScopedFunctor functor([&]() {
    std::lock_guard<std::mutex> lock(*activeTaskCountMutex);
    m_activeTaskCount--;
  });

  while (true) {
    auto state = taskInfo->taskRunner->update(std::move(blackboard));

    if (state == STATE_SUCCESS || state == STATE_FAILURE) {
      if (state == STATE_FAILURE) {
        m_taskFailed = true;
      }
      taskInfo->active = false;
      break;
    }
  }
}

int TaskGroupParallel::getActiveTaskCount() const {
  std::lock_guard<std::mutex> lock(*m_activeTaskCountMutex);
  return m_activeTaskCount;
}
