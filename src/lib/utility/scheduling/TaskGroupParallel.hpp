#pragma once

#include <map>
#include <mutex>
#include <thread>

#include "TaskGroup.hpp"
#include "TaskRunner.hpp"

class TaskGroupParallel : public TaskGroup {
 public:
  TaskGroupParallel();

  void addTask(std::shared_ptr<Task> task) override;

 private:
  struct TaskInfo {
    explicit TaskInfo(std::shared_ptr<TaskRunner> taskRunner) : taskRunner(std::move(taskRunner)), active(false) {}
    std::shared_ptr<TaskRunner> taskRunner;
    std::shared_ptr<std::thread> thread;
    volatile bool active;
  };

  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;
  void doTerminate() override;

  void processTaskThreaded(std::shared_ptr<TaskInfo> taskInfo, std::shared_ptr<Blackboard> blackboard,
                           std::shared_ptr<std::mutex> activeTaskCountMutex);
  int getActiveTaskCount() const;

  std::vector<std::shared_ptr<TaskInfo>> m_tasks;
  bool m_needsToStartThreads;

  volatile bool m_taskFailed;
  volatile int m_activeTaskCount;
  mutable std::shared_ptr<std::mutex> m_activeTaskCountMutex;
};
