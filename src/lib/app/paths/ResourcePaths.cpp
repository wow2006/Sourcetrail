#include "ResourcePaths.h"

#include "AppPath.hpp"
#include "utilityApp.h"

FilePath ResourcePaths::getColorSchemesDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/color_schemes/");
}

FilePath ResourcePaths::getSyntaxHighlightingRulesDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/syntax_highlighting_rules/");
}

FilePath ResourcePaths::getFallbackDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/fallback/");
}

FilePath ResourcePaths::getFontsDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/fonts/");
}

FilePath ResourcePaths::getGuiDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/gui/");
}

FilePath ResourcePaths::getLicenseDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/license/");
}

FilePath ResourcePaths::getJavaDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/java/");
}

FilePath ResourcePaths::getPythonDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/python/");
}

FilePath ResourcePaths::getCxxCompilerHeaderDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/cxx/include/").getCanonical();
}

FilePath ResourcePaths::getPythonIndexerFilePath() {
  if (utility::getOsType() == OS_WINDOWS) {
    return getPythonDirectoryPath().concatenate(L"SourcetrailPythonIndexer.exe");
  }
  return getPythonDirectoryPath().concatenate(L"SourcetrailPythonIndexer");
}
