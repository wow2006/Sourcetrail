#include "FileRegister.h"

namespace utility::file {

FileRegister::FileRegister(const utility::file::FilePath& currentPath,
                           std::set<utility::file::FilePath> indexedPaths,
                           std::set<FilePathFilter> excludeFilters)
    : m_currentPath(currentPath)
    , m_indexedPaths(std::move(indexedPaths))
    , m_excludeFilters(std::move(excludeFilters))
    , m_hasFilePathCache([&](const std::wstring& file) {
      const utility::file::FilePath filePath(file);
      bool ret = false;

      if(filePath == m_currentPath) {
        ret = true;
      }

      if(!ret) {
        for(const utility::file::FilePath& indexedPath: m_indexedPaths) {
          if(indexedPath.isDirectory()) {
            if(indexedPath.contains(filePath)) {
              ret = true;
              break;
            }
          } else {
            if(indexedPath == filePath) {
              ret = true;
              break;
            }
          }
        }
      }

      if(ret) {
        ret = !FilePathFilter::areMatching(m_excludeFilters, filePath);
      }
      return ret;
    }) {}

FileRegister::~FileRegister() = default;

bool FileRegister::hasFilePath(const utility::file::FilePath& filePath) const {
  return m_hasFilePathCache.getValue(filePath.wstr());
}

}    // namespace utility::file
