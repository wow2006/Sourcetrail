#pragma once

#include "TaskGroup.hpp"
#include "TaskRunner.hpp"

class TaskGroupSequence : public TaskGroup {
 public:
  TaskGroupSequence();

  void addTask(std::shared_ptr<Task> task) override;

 private:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;
  void doTerminate() override;

  std::vector<std::shared_ptr<TaskRunner>> m_taskRunners;
  int m_taskIndex;
};
