#include "FileManager.h"
// Internal
#include "FileSystem.h"

namespace utility::file {

void FileManager::update(const std::vector<FilePath>& sourcePaths,
                         const std::vector<FilePathFilter>& excludeFilters,
                         const std::vector<std::wstring>& sourceExtensions) {
  m_sourcePaths = sourcePaths;
  m_excludeFilters = excludeFilters;
  m_sourceExtensions = sourceExtensions;

  m_allSourceFilePaths.clear();

  for(const FileInfo& fileInfo: FileSystem::getFileInfosFromPaths(m_sourcePaths, m_sourceExtensions)) {
    const utility::file::FilePath& filePath = fileInfo.path;
    if(isExcluded(filePath)) {
      continue;
    }

    m_allSourceFilePaths.insert(filePath);
  }
}

std::vector<FilePath> FileManager::getSourcePaths() const {
  return m_sourcePaths;
}

bool FileManager::hasSourceFilePath(const FilePath& filePath) const {
  return m_allSourceFilePaths.find(filePath) != m_allSourceFilePaths.end();
}

std::set<FilePath> FileManager::getAllSourceFilePaths() const {
  return m_allSourceFilePaths;
}

bool FileManager::isExcluded(const FilePath& filePath) const {
  return FilePathFilter::areMatching(m_excludeFilters, filePath);
}

}    // namespace utility::file
