#pragma once
// Internal
#include "FilePath.h"
#include "FilePathFilter.h"
#include "UnorderedCache.h"

namespace utility::file {

class FileRegister {
public:
  FileRegister(const FilePath& currentPath,
               std::set<FilePath> indexedPaths,
               std::set<FilePathFilter> excludeFilters);

  virtual ~FileRegister();

  virtual bool hasFilePath(const FilePath& filePath) const;

private:
  const FilePath& m_currentPath;
  const std::set<FilePath> m_indexedPaths;
  const std::set<FilePathFilter> m_excludeFilters;
  mutable utility::UnorderedCache<std::wstring, bool> m_hasFilePathCache;
};

}    // namespace utility::file
