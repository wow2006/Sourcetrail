#pragma once

#include <set>
#include <string>
#include <vector>

class FilePath;
class FilePathFilter;

class FileManager final {
public:
  void update(const std::vector<FilePath>& sourcePaths,
              const std::vector<FilePathFilter>& excludeFilters,
              const std::vector<std::wstring>& sourceExtensions);

  // returns a list of source paths (can be directories) specified in the project settings
  [[nodiscard]] std::vector<FilePath> getSourcePaths() const;

  // checks if file is in non-excluded source directory
  [[nodiscard]] bool hasSourceFilePath(const FilePath& filePath) const;

  // returns a list of paths to all files that reside in the non-excluded source paths
  [[nodiscard]] std::set<FilePath> getAllSourceFilePaths() const;

private:
  [[nodiscard]] bool isExcluded(const FilePath& filePath) const;

  std::vector<FilePath> m_sourcePaths;
  std::vector<FilePathFilter> m_excludeFilters;
  std::vector<std::wstring> m_sourceExtensions;

  std::set<FilePath> m_allSourceFilePaths;
};
