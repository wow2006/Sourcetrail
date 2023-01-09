#pragma once

namespace utility::file {
class FilePath;
}

class AppPath {
public:
  static utility::file::FilePath getSharedDataDirectoryPath();
  static bool setSharedDataDirectoryPath(const utility::file::FilePath& path);

  static utility::file::FilePath getCxxIndexerFilePath();
  static bool setCxxIndexerDirectoryPath(const utility::file::FilePath& path);

private:
  static utility::file::FilePath s_sharedDataDirectoryPath;
  static utility::file::FilePath s_cxxIndexerDirectoryPath;
};