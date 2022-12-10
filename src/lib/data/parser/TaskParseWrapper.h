#ifndef TASK_PARSE_WRAPPER_H
#define TASK_PARSE_WRAPPER_H

#include <memory>

#include "Task.hpp"
#include "TaskDecorator.h"
#include "TaskRunner.hpp"
#include "TimeStamp.h"

class DialogView;
class FileRegister;
class PersistentStorage;

class TaskParseWrapper : public TaskDecorator {
 public:
  TaskParseWrapper(std::weak_ptr<PersistentStorage> storage, std::shared_ptr<DialogView> dialogView);

 private:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;

  std::weak_ptr<PersistentStorage> m_storage;
  std::shared_ptr<DialogView> m_dialogView;

  TimeStamp m_start;
};

#endif  // TASK_PARSE_WRAPPER_H
