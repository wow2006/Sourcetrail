#include "ResourcePaths.hpp"

#include "AppPath.hpp"
#include "utilityApp.h"


namespace resourcePaths {
FilePath getColorSchemesDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/color_schemes/");
}

FilePath getSyntaxHighlightingRulesDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/syntax_highlighting_rules/");
}

FilePath getFallbackDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/fallback/");
}

FilePath getFontsDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/fonts/");
}

FilePath getGuiDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/gui/");
}

FilePath getLicenseDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/license/");
}

FilePath getJavaDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/java/");
}

FilePath getPythonDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/python/");
}

FilePath getCxxCompilerHeaderDirectoryPath() {
  return appPath::getSharedDataDirectoryPath().concatenate(L"data/cxx/include/").getCanonical();
}

FilePath getPythonIndexerFilePath() {
  if (utility::getOsType() == OS_WINDOWS) {
    return getPythonDirectoryPath().concatenate(L"SourcetrailPythonIndexer.exe");
  }
  return getPythonDirectoryPath().concatenate(L"SourcetrailPythonIndexer");
}
}