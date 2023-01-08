#pragma once

#include "FilePath.h"
#include "FilePathFilter.h"
#include "IndexerCommandType.h"

class QJsonObject;

class IndexerCommand {
public:
  static std::wstring serialize(const std::shared_ptr<IndexerCommand>& indexerCommand,
                                bool compact = true);

  IndexerCommand(FilePath sourceFilePath);

  virtual ~IndexerCommand();

  virtual IndexerCommandType getIndexerCommandType() const = 0;

  virtual size_t getByteSize(size_t stringSize) const;

  const FilePath& getSourceFilePath() const;

protected:
  virtual QJsonObject doSerialize() const;

private:
  FilePath m_sourceFilePath;
};
