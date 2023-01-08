#pragma once

#include "TaskDecorator.h"
#include "TaskRunner.h"
#include "TimeStamp.h"

class TaskDecoratorDelay : public TaskDecorator {
public:
  TaskDecoratorDelay(size_t delayMS);

private:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;
  void doTerminate() override;

  const size_t m_delayMS;

  TimeStamp m_start;
  bool m_delayComplete;
};
