#include "ResourcePaths.h"

#include "AppPath.h"
#include "utility/utilityApp.h"

utility::file::FilePath ResourcePaths::getColorSchemesDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/color_schemes/");
}

utility::file::FilePath ResourcePaths::getSyntaxHighlightingRulesDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/syntax_highlighting_rules/");
}

utility::file::FilePath ResourcePaths::getFallbackDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/fallback/");
}

utility::file::FilePath ResourcePaths::getFontsDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/fonts/");
}

utility::file::FilePath ResourcePaths::getGuiDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/gui/");
}

utility::file::FilePath ResourcePaths::getLicenseDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/license/");
}

utility::file::FilePath ResourcePaths::getJavaDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/java/");
}

utility::file::FilePath ResourcePaths::getPythonDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/python/");
}

utility::file::FilePath ResourcePaths::getCxxCompilerHeaderDirectoryPath() {
  return AppPath::getSharedDataDirectoryPath().concatenate(L"data/cxx/include/").getCanonical();
}

utility::file::FilePath ResourcePaths::getPythonIndexerFilePath() {
  if(utility::getOsType() == OS_WINDOWS) {
    return getPythonDirectoryPath().concatenate(L"SourcetrailPythonIndexer.exe");
  }
  return getPythonDirectoryPath().concatenate(L"SourcetrailPythonIndexer");
}
