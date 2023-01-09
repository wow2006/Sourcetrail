#pragma once

#include "IndexerCommand.h"

class IndexerCommandCustom : public IndexerCommand {
public:
  static IndexerCommandType getStaticIndexerCommandType();

  IndexerCommandCustom(const std::wstring& command,
                       const std::vector<std::wstring>& arguments,
                       const utility::file::FilePath& projectFilePath,
                       const utility::file::FilePath& databaseFilePath,
                       const std::wstring& databaseVersion,
                       const utility::file::FilePath& sourceFilePath,
                       bool runInParallel);

  IndexerCommandCustom(IndexerCommandType type,
                       const std::wstring& command,
                       const std::vector<std::wstring>& arguments,
                       const utility::file::FilePath& projectFilePath,
                       const utility::file::FilePath& databaseFilePath,
                       const std::wstring& databaseVersion,
                       const utility::file::FilePath& sourceFilePath,
                       bool runInParallel);

  ~IndexerCommandCustom() override;

  IndexerCommandType getIndexerCommandType() const override;

  size_t getByteSize(size_t stringSize) const override;

  utility::file::FilePath getDatabaseFilePath() const;

  void setDatabaseFilePath(const utility::file::FilePath& databaseFilePath);

  std::wstring getCommand() const;

  std::vector<std::wstring> getArguments() const;

  bool getRunInParallel() const;

protected:
  QJsonObject doSerialize() const override;

private:
  std::wstring replaceVariables(std::wstring s) const;

  IndexerCommandType m_type;
  std::wstring m_command;
  std::vector<std::wstring> m_arguments;
  utility::file::FilePath m_projectFilePath;
  utility::file::FilePath m_databaseFilePath;
  std::wstring m_databaseVersion;
  bool m_runInParallel;
};
