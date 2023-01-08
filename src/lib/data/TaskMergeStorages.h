#pragma once

#include "Task.h"

class StorageProvider;

class TaskMergeStorages : public Task {
public:
  TaskMergeStorages(std::shared_ptr<StorageProvider> storageProvider);

private:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;

  std::shared_ptr<StorageProvider> m_storageProvider;
};