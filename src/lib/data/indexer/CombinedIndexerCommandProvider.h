#pragma once

#include "IndexerCommandProvider.h"

class CombinedIndexerCommandProvider : public IndexerCommandProvider {
public:
  void addProvider(std::shared_ptr<IndexerCommandProvider> provider);

  std::vector<utility::file::FilePath> getAllSourceFilePaths() const override;
  std::shared_ptr<IndexerCommand> consumeCommand() override;
  std::shared_ptr<IndexerCommand> consumeCommandForSourceFilePath(const utility::file::FilePath& filePath) override;
  std::vector<std::shared_ptr<IndexerCommand>> consumeAllCommands() override;

  void clear() override;
  size_t size() const override;

private:
  std::vector<std::shared_ptr<IndexerCommandProvider>> m_providers;
};
