#pragma once

#include "IndexerCommandType.h"

class FileRegister;
class IndexerCommand;
class IntermediateStorage;

class IndexerBase {
public:
  IndexerBase();
  virtual ~IndexerBase();

  virtual IndexerCommandType getSupportedIndexerCommandType() const = 0;
  virtual std::shared_ptr<IntermediateStorage> index(std::shared_ptr<IndexerCommand> indexerCommand) = 0;
  virtual void interrupt() = 0;
};
