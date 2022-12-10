#ifndef TASK_DECORATOR_REPEAT_H
#define TASK_DECORATOR_REPEAT_H

#include <vector>

#include "TaskDecorator.h"
#include "TaskRunner.hpp"

class TaskDecoratorRepeat : public TaskDecorator {
 public:
  enum ConditionType { CONDITION_WHILE_SUCCESS };

  TaskDecoratorRepeat(ConditionType condition, TaskState exitState, size_t delayMS);

 private:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;

  const ConditionType m_condition;
  const TaskState m_exitState;
  const size_t m_delayMS;
};

#endif  // TASK_DECORATOR_REPEAT_H
