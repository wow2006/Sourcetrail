#pragma once

#include "Task.h"
#include "TimeStamp.h"

class DialogView;
#include "FilePath.h"
class PersistentStorage;

class TaskCleanStorage : public Task {
public:
  TaskCleanStorage(std::weak_ptr<PersistentStorage> storage,
                   std::shared_ptr<DialogView> dialogView,
                   const std::vector<utility::file::FilePath>& filePaths,
                   bool clearAllErrors);

private:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;

  std::weak_ptr<PersistentStorage> m_storage;
  std::shared_ptr<DialogView> m_dialogView;
  std::vector<utility::file::FilePath> m_filePaths;
  bool m_clearAllErrors;

  TimeStamp m_start;
};