#include "AppPath.h"

#include "utility/utilityApp.h"

utility::file::FilePath AppPath::s_sharedDataDirectoryPath(L"");
utility::file::FilePath AppPath::s_cxxIndexerDirectoryPath(L"");

utility::file::FilePath AppPath::getSharedDataDirectoryPath() {
  return s_sharedDataDirectoryPath;
}

bool AppPath::setSharedDataDirectoryPath(const utility::file::FilePath& path) {
  if(!path.empty()) {
    s_sharedDataDirectoryPath = path;
    return true;
  }
  return false;
}

utility::file::FilePath AppPath::getCxxIndexerFilePath() {
  std::wstring cxxIndexerName(L"sourcetrail_indexer");
  if(utility::getOsType() == OS_WINDOWS) {
    cxxIndexerName = L"sourcetrail_indexer.exe";
  }

  if(!s_cxxIndexerDirectoryPath.empty()) {
    return s_cxxIndexerDirectoryPath.getConcatenated(cxxIndexerName);
  }
  return s_sharedDataDirectoryPath.getConcatenated(cxxIndexerName);
}

bool AppPath::setCxxIndexerDirectoryPath(const utility::file::FilePath& path) {
  if(!path.empty()) {
    s_cxxIndexerDirectoryPath = path;
    return true;
  }
  return false;
}
