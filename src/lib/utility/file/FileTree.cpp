#include "FileTree.h"

#include "FileSystem.h"

namespace utility::file {

FileTree::FileTree(const FilePath& rootPath): m_rootPath(rootPath.getAbsolute().makeCanonical()) {
  if(m_rootPath.exists()) {
    if(m_rootPath.isDirectory()) {
      for(const auto& filePath : FileSystem::getFilePathsFromDirectory(m_rootPath)) {
        m_files[filePath.fileName()].insert(filePath);
      }
    } else {
      m_files[m_rootPath.fileName()].insert(m_rootPath);
    }
  }
}

FilePath FileTree::getAbsoluteRootPathForRelativeFilePath(const FilePath& relativeFilePath) const {
  const auto rootPaths = doGetAbsoluteRootPathsForRelativeFilePath(relativeFilePath, false);
  if(rootPaths.empty()) {
    return {};
  }

  return rootPaths.front();
}

std::vector<FilePath> FileTree::getAbsoluteRootPathsForRelativeFilePath(
    const FilePath& relativeFilePath) const {
  return doGetAbsoluteRootPathsForRelativeFilePath(relativeFilePath, true);
}

std::vector<FilePath> FileTree::doGetAbsoluteRootPathsForRelativeFilePath(
    const FilePath& relativeFilePath, bool allowMultipleResults) const {
  std::vector<FilePath> rootPaths;

  auto iterator = m_files.find(relativeFilePath.fileName());
  if(iterator != m_files.end()) {
    for(FilePath existingFilePath : iterator->second) {
      existingFilePath = existingFilePath.getParentDirectory();
      bool ok = true;
      {
        auto temp = relativeFilePath.getParentDirectory();
        while(!temp.empty()) {
          if(temp.fileName() == L"..") {
            auto subDirectories = FileSystem::getDirectSubDirectories(existingFilePath);
            if(!subDirectories.empty()) {
              existingFilePath = subDirectories.front();
            } else {
              ok = false;
              break;
            }
          } else {
            existingFilePath = existingFilePath.getParentDirectory();
          }
          temp = temp.getParentDirectory();
        }
      }

      if(ok) {
        rootPaths.push_back(existingFilePath);
        if(!allowMultipleResults) {
          break;
        }
      }
    }
  }
  return rootPaths;
}

}    // namespace utility::file
