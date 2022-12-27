#pragma once
// STL
#include <cstdint>
#include <set>
#include <string>
#include <vector>
// Internal
#include "FileInfo.h"
#include "TimeStamp.h"

class FileSystem final {
public:
  static std::vector<FilePath> getFilePathsFromDirectory(
      const FilePath& path, const std::vector<std::wstring>& extensions = {});

  static FileInfo getFileInfoForPath(const FilePath& filePath);

  static std::vector<FileInfo> getFileInfosFromPaths(const std::vector<FilePath>& paths,
                                                     const std::vector<std::wstring>& fileExtensions,
                                                     bool followSymLinks = true);

  static std::set<FilePath> getSymLinkedDirectories(const FilePath& path);
  static std::set<FilePath> getSymLinkedDirectories(const std::vector<FilePath>& paths);

  static uint64_t getFileByteSize(const FilePath& filePath);

  static TimeStamp getLastWriteTime(const FilePath& filePath);

  static bool remove(const FilePath& path);
  static bool rename(const FilePath& fromPath, const FilePath& toPath);

  static bool copyFile(const FilePath& fromPath, const FilePath& toPath);
  static bool copy_directory(const FilePath& fromPath, const FilePath& toPath);

  static void createDirectory(const FilePath& path);
  static std::vector<FilePath> getDirectSubDirectories(const FilePath& path);
  static std::vector<FilePath> getRecursiveSubDirectories(const FilePath& path);
};
