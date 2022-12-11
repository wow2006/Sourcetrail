#pragma once

#include <mutex>
#include <thread>

#include "TaskGroup.hpp"

class TaskGroupParallel final : public TaskGroup {
 public:
  TaskGroupParallel();

  TaskGroupParallel(const TaskGroupParallel&) = delete;
  TaskGroupParallel(TaskGroupParallel&&) = delete;
  TaskGroupParallel& operator=(const TaskGroupParallel&) = delete;
  TaskGroupParallel& operator=(TaskGroupParallel&&) = delete;

  ~TaskGroupParallel() override;

  void addTask(std::shared_ptr<Task> task) override;

 private:
  struct TaskInfo;

  void doEnter(std::shared_ptr<Blackboard> blackboard) override;

  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;

  void doExit(std::shared_ptr<Blackboard> blackboard) override;

  void doReset(std::shared_ptr<Blackboard> blackboard) override;

  void doTerminate() override;

  void processTaskThreaded(const std::shared_ptr<TaskInfo>& taskInfo, std::shared_ptr<Blackboard> blackboard,
                           const std::shared_ptr<std::mutex>& activeTaskCountMutex);

  int getActiveTaskCount() const;

  std::vector<std::shared_ptr<TaskInfo>> m_tasks;
  bool m_needsToStartThreads = true;

  volatile bool m_taskFailed = false;
  volatile int m_activeTaskCount = 0;
  mutable std::shared_ptr<std::mutex> m_activeTaskCountMutex = std::make_shared<std::mutex>();
};
