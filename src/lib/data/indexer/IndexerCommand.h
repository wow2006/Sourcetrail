#pragma once

#include "FilePath.h"
#include "FilePathFilter.h"
#include "IndexerCommandType.h"

class QJsonObject;

class IndexerCommand {
public:
  static std::wstring serialize(const std::shared_ptr<IndexerCommand>& indexerCommand,
                                bool compact = true);

  IndexerCommand(utility::file::FilePath sourceFilePath);

  virtual ~IndexerCommand();

  virtual IndexerCommandType getIndexerCommandType() const = 0;

  virtual size_t getByteSize(size_t stringSize) const;

  const utility::file::FilePath& getSourceFilePath() const;

protected:
  virtual QJsonObject doSerialize() const;

private:
  utility::file::FilePath m_sourceFilePath;
};
