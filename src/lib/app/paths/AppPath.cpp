#include "AppPath.hpp"

#include "FilePath.hpp"
#include "utilityApp.h"

FilePath s_sharedDataDirectoryPath(L"");
FilePath s_cxxIndexerDirectoryPath(L"");

namespace appPath {

FilePath getSharedDataDirectoryPath() { return s_sharedDataDirectoryPath; }

bool appPath::setSharedDataDirectoryPath(const FilePath& path) {
  if (!path.empty()) {
    s_sharedDataDirectoryPath = path;
    return true;
  }
  return false;
}

FilePath getCxxIndexerFilePath() {
  std::wstring cxxIndexerName(L"sourcetrail_indexer");
  if (utility::getOsType() == OS_WINDOWS) {
    cxxIndexerName = L"sourcetrail_indexer.exe";
  }

  if (!s_cxxIndexerDirectoryPath.empty()) {
    return s_cxxIndexerDirectoryPath.getConcatenated(cxxIndexerName);
  }
  return s_sharedDataDirectoryPath.getConcatenated(cxxIndexerName);
}

bool setCxxIndexerDirectoryPath(const FilePath& path) {
  if (!path.empty()) {
    s_cxxIndexerDirectoryPath = path;
    return true;
  }
  return false;
}

}  // namespace appPath