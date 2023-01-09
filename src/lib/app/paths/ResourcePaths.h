#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file

class ResourcePaths {
public:
  static utility::file::FilePath getColorSchemesDirectoryPath();
  static utility::file::FilePath getSyntaxHighlightingRulesDirectoryPath();
  static utility::file::FilePath getFallbackDirectoryPath();
  static utility::file::FilePath getFontsDirectoryPath();
  static utility::file::FilePath getGuiDirectoryPath();
  static utility::file::FilePath getLicenseDirectoryPath();
  static utility::file::FilePath getJavaDirectoryPath();
  static utility::file::FilePath getPythonDirectoryPath();
  static utility::file::FilePath getCxxCompilerHeaderDirectoryPath();
  static utility::file::FilePath getPythonIndexerFilePath();
};