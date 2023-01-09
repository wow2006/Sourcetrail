#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <memory>

#include "IndexerCommandProvider.h"
#include "utility/types.h"

class IndexerCommandCxx;

class CxxIndexerCommandProvider : public IndexerCommandProvider {
public:
  CxxIndexerCommandProvider();

  void addCommand(const std::shared_ptr<IndexerCommandCxx>& command);

  std::vector<utility::file::FilePath> getAllSourceFilePaths() const override;

  std::shared_ptr<IndexerCommand> consumeCommand() override;

  std::shared_ptr<IndexerCommand> consumeCommandForSourceFilePath(const utility::file::FilePath& filePath) override;

  std::vector<std::shared_ptr<IndexerCommand>> consumeAllCommands() override;

  void clear() override;

  size_t size() const override;

  void logStats() const;

private:
  struct CommandRepresentation {
    std::set<Id> m_indexedPathIds;
    std::set<Id> m_excludeFilterIds;
    std::set<Id> m_includeFilterIds;
    Id m_workingDirectoryId;
    std::vector<Id> m_compilerFlagIds;
  };

  Id getId();

  std::shared_ptr<IndexerCommandCxx> representationToCommand(
      const utility::file::FilePath& sourceFilePath, std::shared_ptr<CommandRepresentation> representation);

  Id m_nextId;

  std::multimap<utility::file::FilePath, std::shared_ptr<CommandRepresentation>> m_commands;

  std::map<Id, utility::file::FilePath> m_idsToIndexedPaths;
  std::map<utility::file::FilePath, Id> m_indexedPathsToIds;
  std::map<Id, std::wstring> m_idsToExcludeFilters;
  std::map<std::wstring, Id> m_excludeFiltersToIds;
  std::map<Id, std::wstring> m_idsToIncludeFilters;
  std::map<std::wstring, Id> m_includeFiltersToIds;
  std::map<Id, utility::file::FilePath> m_idsToWorkingDirectories;
  std::map<utility::file::FilePath, Id> m_workingDirectoriesToIds;
  std::map<Id, std::wstring> m_idsToCompilerFlags;
  std::unordered_map<std::wstring, Id> m_compilerFlagsToIds;
};
