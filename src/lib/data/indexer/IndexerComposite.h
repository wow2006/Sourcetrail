#pragma once

#include "IndexerBase.h"

class IndexerComposite : public IndexerBase {
public:
  ~IndexerComposite() override;

  IndexerCommandType getSupportedIndexerCommandType() const override;

  void addIndexer(std::shared_ptr<IndexerBase> indexer);

  std::shared_ptr<IntermediateStorage> index(std::shared_ptr<IndexerCommand> indexerCommand) override;

  void interrupt() override;

private:
  std::map<IndexerCommandType, std::shared_ptr<IndexerBase>> m_indexers;
};
