#pragma once
// Internal
#include "FilePath.h"

namespace utility::file {

/**
 * @brief FileTree class used for caching files in a directory.
 */
class FileTree {
public:
  /**
   * Create a FileTree object. It will read all the files in given directory recursively.
   *
   * @brief Constructor.
   *
   * @param rootPath file/directory to cache.
   *
   * @note if the argment is a file, that file will only be cached.
   * @note if the argment is an empty, FilePath will behave as "." dir.
   * @note if the file isn't exist nothing will be cached.
   */
  explicit FileTree(const FilePath& rootPath);

  FilePath getAbsoluteRootPathForRelativeFilePath(const FilePath& relativeFilePath) const;

  std::vector<FilePath> getAbsoluteRootPathsForRelativeFilePath(const FilePath& relativeFilePath) const;

private:
  std::vector<FilePath> doGetAbsoluteRootPathsForRelativeFilePath(const FilePath& relativeFilePath,
                                                                  bool allowMultipleResults) const;

  FilePath m_rootPath;
  std::unordered_map<std::wstring, std::set<FilePath>> m_files;
};

}    // namespace utility::file
