#include "IndexerCommand.h"

#include <QJsonDocument>
#include <QJsonObject>

#include "utilityString.h"

std::wstring IndexerCommand::serialize(const std::shared_ptr<IndexerCommand>& indexerCommand,
                                       bool compact) {
  QJsonDocument jsonDocument(indexerCommand->doSerialize());
  return QString::fromUtf8(
             jsonDocument.toJson(compact ? QJsonDocument::Compact : QJsonDocument::Indented))
      .toStdWString();
}

IndexerCommand::IndexerCommand(FilePath sourceFilePath): m_sourceFilePath(std::move(sourceFilePath)) {}

IndexerCommand::~IndexerCommand() = default;

size_t IndexerCommand::getByteSize(size_t /*stringSize*/) const {
  return utility::encodeToUtf8(m_sourceFilePath.wstr()).size();
}

const FilePath& IndexerCommand::getSourceFilePath() const {
  return m_sourceFilePath;
}

QJsonObject IndexerCommand::doSerialize() const {
  QJsonObject jsonObject;

  {
    jsonObject["type"] = QString::fromStdString(indexerCommandTypeToString(getIndexerCommandType()));
  }
  { jsonObject["source_file_path"] = QString::fromStdWString(m_sourceFilePath.wstr()); }

  return jsonObject;
}
