#pragma once
// Internal
#include "FileInfo.h"
#include "TimeStamp.h"

namespace utility::file {

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

  /**
   * @brief Get all recursive subDirectories
   *
   * @param path Root path
   *
   * @note empty input and not exists will return empty list
   *
   * @return A list of subDirectories
   */
  static std::vector<FilePath> getRecursiveSubDirectories(const FilePath& path);
};

}    // namespace utility::file
