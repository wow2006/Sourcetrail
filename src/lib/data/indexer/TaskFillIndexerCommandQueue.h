#pragma once

#include "MessageIndexingInterrupted.h"
#include "MessageListener.h"
#include "Task.h"

#include "InterprocessIndexerCommandManager.h"

class IndexerCommandProvider;

class TaskFillIndexerCommandsQueue
    : public Task
    , public MessageListener<MessageIndexingInterrupted> {
public:
  TaskFillIndexerCommandsQueue(const std::string& appUUID,
                               std::unique_ptr<IndexerCommandProvider> indexerCommandProvider,
                               size_t maximumQueueSize);

  ~TaskFillIndexerCommandsQueue();

protected:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;
  void terminate() override;

  void handleMessage(MessageIndexingInterrupted* message) override;

  bool fillCommandQueue();

private:
  std::unique_ptr<IndexerCommandProvider> m_indexerCommandProvider;
  InterprocessIndexerCommandManager m_indexerCommandManager;

  const size_t m_maximumQueueSize;

  std::queue<utility::file::FilePath> m_filePathQueue;
  std::mutex m_commandsMutex;

  bool m_interrupted = false;
};