#include "SourceGroup.h"

#include "FilePath.h"
#include "FilePathFilter.h"
#include "MemoryIndexerCommandProvider.h"
#include "SourceGroupSettings.h"
#include "TaskLambda.h"

SourceGroup::~SourceGroup() = default;

std::shared_ptr<IndexerCommandProvider> SourceGroup::getIndexerCommandProvider(
    const RefreshInfo& info) const {
  return std::make_shared<MemoryIndexerCommandProvider>(getIndexerCommands(info));
}

std::shared_ptr<Task> SourceGroup::getPreIndexTask(std::shared_ptr<StorageProvider> /*storageProvider*/,
                                                   std::shared_ptr<DialogView> /*dialogView*/) const {
  return std::make_shared<TaskLambda>([]() {});
}

SourceGroupType SourceGroup::getType() const {
  return getSourceGroupSettings()->getType();
}

LanguageType SourceGroup::getLanguage() const {
  return getSourceGroupSettings()->getLanguage();
}

SourceGroupStatusType SourceGroup::getStatus() const {
  return getSourceGroupSettings()->getStatus();
}

bool SourceGroup::prepareIndexing() {
  return true;
}

bool SourceGroup::allowsPartialClearing() const {
  return true;
}

bool SourceGroup::allowsShallowIndexing() const {
  return false;
}

std::set<utility::file::FilePath> SourceGroup::filterToContainedSourceFilePath(
    const std::set<utility::file::FilePath>& sourceFilePaths) const {
  std::set<utility::file::FilePath> filteredSourceFilePaths;
  for(const utility::file::FilePath& sourceFilePath: getAllSourceFilePaths()) {
    if(sourceFilePaths.find(sourceFilePath) == sourceFilePaths.end()) {
      filteredSourceFilePaths.insert(sourceFilePath);
    }
  }
  return filteredSourceFilePaths;
}

bool SourceGroup::containsSourceFilePath(const utility::file::FilePath& sourceFilePath) const {
  return !filterToContainedSourceFilePath({sourceFilePath}).empty();
}

std::set<utility::file::FilePath> SourceGroup::filterToContainedFilePaths(
    const std::set<utility::file::FilePath>& filePaths,
    const std::set<utility::file::FilePath>& indexedFilePaths,
    const std::set<utility::file::FilePath>& indexedFileOrDirectoryPaths,
    const std::vector<utility::file::FilePathFilter>& excludeFilters) const {
  std::set<utility::file::FilePath> containedFilePaths;

  for(const utility::file::FilePath& filePath: filePaths) {
    bool isInIndexedPaths = false;

    for(const utility::file::FilePath& indexedFileOrDirectoryPath: indexedFileOrDirectoryPaths) {
      if(indexedFileOrDirectoryPath == filePath || indexedFileOrDirectoryPath.contains(filePath)) {
        isInIndexedPaths = true;
        break;
      }
    }

    if(!isInIndexedPaths && indexedFilePaths.find(filePath) != indexedFilePaths.end()) {
      isInIndexedPaths = true;
    }

    if(isInIndexedPaths) {
      isInIndexedPaths = !utility::file::FilePathFilter::areMatching(excludeFilters, filePath);
    }

    if(isInIndexedPaths) {
      containedFilePaths.insert(filePath);
    }
  }

  return containedFilePaths;
}
