#pragma once

#include "ErrorCountInfo.h"
#include "FilePath.h"
#include "MessageIndexingInterrupted.h"
#include "MessageListener.h"
#include "Task.h"
#include "TimeStamp.h"

class DialogView;
class IndexerCommandCustom;
class IndexerCommandProvider;
class PersistentStorage;

class TaskExecuteCustomCommands
    : public Task
    , public MessageListener<MessageIndexingInterrupted> {
public:
  static void runPythonPostProcessing(PersistentStorage& storage);

  TaskExecuteCustomCommands(std::unique_ptr<IndexerCommandProvider> indexerCommandProvider,
                            std::shared_ptr<PersistentStorage> storage,
                            std::shared_ptr<DialogView> dialogView,
                            size_t indexerThreadCount,
                            const utility::file::FilePath& projectDirectory);

  ~TaskExecuteCustomCommands() override;

private:
  void doEnter(std::shared_ptr<Blackboard> blackboard) override;
  TaskState doUpdate(std::shared_ptr<Blackboard> blackboard) override;
  void doExit(std::shared_ptr<Blackboard> blackboard) override;
  void doReset(std::shared_ptr<Blackboard> blackboard) override;

  void handleMessage(MessageIndexingInterrupted* message) override;

  void executeParallelIndexerCommands(int threadId, std::shared_ptr<Blackboard> blackboard);
  void runIndexerCommand(std::shared_ptr<IndexerCommandCustom> indexerCommand,
                         std::shared_ptr<Blackboard> blackboard,
                         std::shared_ptr<PersistentStorage> storage);

  std::unique_ptr<IndexerCommandProvider> m_indexerCommandProvider;
  std::shared_ptr<PersistentStorage> m_storage;
  std::shared_ptr<DialogView> m_dialogView;
  const size_t m_indexerThreadCount;
  const utility::file::FilePath m_projectDirectory;

  TimeStamp m_start;
  bool m_interrupted = false;
  size_t m_indexerCommandCount;
  std::vector<std::shared_ptr<IndexerCommandCustom>> m_serialCommands;
  std::vector<std::shared_ptr<IndexerCommandCustom>> m_parallelCommands;
  std::mutex m_parallelCommandsMutex;
  ErrorCountInfo m_errorCount;
  std::mutex m_errorCountMutex;
  utility::file::FilePath m_targetDatabaseFilePath;
  bool m_hasPythonCommands;
  std::set<utility::file::FilePath> m_sourceDatabaseFilePaths;
  std::mutex m_sourceDatabaseFilePathsMutex;
};