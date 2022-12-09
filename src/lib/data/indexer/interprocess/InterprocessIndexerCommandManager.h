#ifndef INTERPROCESS_INDEXER_COMMAND_MANAGER_H
#define INTERPROCESS_INDEXER_COMMAND_MANAGER_H

#include "BaseInterprocessDataManager.h"
#include "SharedIndexerCommand.h"

class IndexerCommand;

class InterprocessIndexerCommandManager final : public BaseInterprocessDataManager {
 public:
  InterprocessIndexerCommandManager(const std::string& instanceUuid, Id processId, bool isOwner);
  ~InterprocessIndexerCommandManager() override;

  void pushIndexerCommands(const std::vector<std::shared_ptr<IndexerCommand>>& indexerCommands);
  std::shared_ptr<IndexerCommand> popIndexerCommand();

  void clearIndexerCommands();
  size_t indexerCommandCount();

 private:
  static constexpr std::string_view s_sharedMemoryNamePrefix = "icmd_";
  static constexpr std::string_view s_indexerCommandsKeyName = "indexer_commands";
};

#endif  // INTERPROCESS_INDEXER_COMMAND_MANAGER_H
