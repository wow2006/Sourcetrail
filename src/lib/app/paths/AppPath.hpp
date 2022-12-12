#pragma once

class FilePath;

namespace appPath {
  FilePath getSharedDataDirectoryPath();

  bool setSharedDataDirectoryPath(const FilePath& path);

  FilePath getCxxIndexerFilePath();

  bool setCxxIndexerDirectoryPath(const FilePath& path);
};
