#pragma once

#include "LanguageType.h"
#include "SourceGroupStatusType.h"
#include "SourceGroupType.h"

class DialogView;
namespace utility::file {
class FilePath;
class FilePathFilter;
} // namespace class utility::file
class IndexerCommand;
class IndexerCommandProvider;
class SourceGroupSettings;
class StorageProvider;
class Task;

struct RefreshInfo;

class SourceGroup {
public:
  virtual ~SourceGroup();

  virtual bool prepareIndexing();
  virtual bool allowsPartialClearing() const;
  virtual bool allowsShallowIndexing() const;

  virtual std::set<utility::file::FilePath> filterToContainedFilePaths(const std::set<utility::file::FilePath>& filePaths) const = 0;
  virtual std::set<utility::file::FilePath> getAllSourceFilePaths() const = 0;
  virtual std::shared_ptr<IndexerCommandProvider> getIndexerCommandProvider(const RefreshInfo& info) const;
  virtual std::vector<std::shared_ptr<IndexerCommand>> getIndexerCommands(
      const RefreshInfo& info) const = 0;
  virtual std::shared_ptr<Task> getPreIndexTask(std::shared_ptr<StorageProvider> storageProvider,
                                                std::shared_ptr<DialogView> dialogView) const;

  SourceGroupType getType() const;
  LanguageType getLanguage() const;
  SourceGroupStatusType getStatus() const;
  std::set<utility::file::FilePath> filterToContainedSourceFilePath(
      const std::set<utility::file::FilePath>& staticSourceFilePaths) const;
  bool containsSourceFilePath(const utility::file::FilePath& sourceFilePath) const;

protected:
  virtual std::shared_ptr<SourceGroupSettings> getSourceGroupSettings() = 0;
  virtual std::shared_ptr<const SourceGroupSettings> getSourceGroupSettings() const = 0;

  std::set<utility::file::FilePath> filterToContainedFilePaths(const std::set<utility::file::FilePath>& filePaths,
                                                const std::set<utility::file::FilePath>& indexedFilePaths,
                                                const std::set<utility::file::FilePath>& indexedFileOrDirectoryPaths,
                                                const std::vector<utility::file::FilePathFilter>& excludeFilters) const;
};