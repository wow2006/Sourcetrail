#pragma once
// Internal
#include "FilePath.h"
#include "FilePathFilter.h"

namespace utility::file {

/**
 * @brief a file manager
 */
class FileManager final {
public:
  void update(const std::vector<FilePath>& sourcePaths,
              const std::vector<FilePathFilter>& excludeFilters,
              const std::vector<std::wstring>& sourceExtensions);

  /**
   * @brief returns a list of source paths (can be directories) specified in the project settings
   *
   * @return a list of source paths
   */
  [[nodiscard]] std::vector<FilePath> getSourcePaths() const;

  /**
   * @brief checks if file is in non-excluded source directory
   *
   * @param filePath file to check
   *
   * @return if file is in non-excluded source directory
   */
  [[nodiscard]] bool hasSourceFilePath(const FilePath& filePath) const;

  /**
   * @brief returns a list of paths to all files that reside in the non-excluded source paths
   *
   * @return a list of paths
   */
  [[nodiscard]] std::set<FilePath> getAllSourceFilePaths() const;

private:
  [[nodiscard]] bool isExcluded(const FilePath& filePath) const;

  std::vector<FilePath> m_sourcePaths;
  std::vector<FilePathFilter> m_excludeFilters;
  std::vector<std::wstring> m_sourceExtensions;

  std::set<FilePath> m_allSourceFilePaths;
};

}    // namespace utility::file
