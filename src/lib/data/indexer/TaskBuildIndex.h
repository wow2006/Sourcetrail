#ifndef TASK_BUILD_INDEX_H
#define TASK_BUILD_INDEX_H

#include <thread>

#include "InterprocessIndexerCommandManager.h"
#include "InterprocessIndexingStatusManager.h"
#include "InterprocessIntermediateStorageManager.h"
#include "MessageIndexingInterrupted.h"
#include "MessageListener.h"
#include "Task.hpp"

class DialogView;
class StorageProvider;
class IndexerCommandList;

class TaskBuildIndex : public Task, public MessageListener<MessageIndexingInterrupted> {
 public:
  TaskBuildIndex(size_t processCount, std::shared_ptr<StorageProvider> storageProvider,
                 std::shared_ptr<DialogView> dialogView, const std::string& appUUID, bool multiProcessIndexing);

 protected:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;
  void terminate() override;

  void handleMessage(MessageIndexingInterrupted* message) override;

  void runIndexerProcess(int processId, const std::wstring& logFilePath);
  void runIndexerThread(int processId);
  bool fetchIntermediateStorages(std::shared_ptr<Blackboard> blackboard);
  void updateIndexingDialog(std::shared_ptr<Blackboard> blackboard, const std::vector<FilePath>& sourcePaths);

  static const std::wstring s_processName;

  std::shared_ptr<IndexerCommandList> m_indexerCommandList;
  std::shared_ptr<StorageProvider> m_storageProvider;
  std::shared_ptr<DialogView> m_dialogView;
  const std::string m_appUUID;
  bool m_multiProcessIndexing;

  InterprocessIndexingStatusManager m_interprocessIndexingStatusManager;
  bool m_indexerCommandQueueStopped;
  size_t m_processCount;
  bool m_interrupted;
  size_t m_indexingFileCount;

  // store as plain pointers to avoid deallocation issues when closing app during indexing
  std::vector<std::thread*> m_processThreads;
  std::vector<std::shared_ptr<InterprocessIntermediateStorageManager>> m_interprocessIntermediateStorageManagers;

  size_t m_runningThreadCount;
  std::mutex m_runningThreadCountMutex;
};

#endif  // TASK_PARSE_H
