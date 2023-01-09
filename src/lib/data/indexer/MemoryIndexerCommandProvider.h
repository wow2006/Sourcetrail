#pragma once

#include "IndexerCommandProvider.h"

class MemoryIndexerCommandProvider : public IndexerCommandProvider {
public:
  MemoryIndexerCommandProvider(const std::vector<std::shared_ptr<IndexerCommand>>& commands);

	~MemoryIndexerCommandProvider() override;

  std::vector<utility::file::FilePath> getAllSourceFilePaths() const override;

  std::shared_ptr<IndexerCommand> consumeCommand() override;

  std::shared_ptr<IndexerCommand> consumeCommandForSourceFilePath(const utility::file::FilePath& filePath) override;

  std::vector<std::shared_ptr<IndexerCommand>> consumeAllCommands() override;

  void clear() override;

  size_t size() const override;

private:
  std::map<utility::file::FilePath, std::shared_ptr<IndexerCommand>> m_commands;
};