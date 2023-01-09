#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file

enum RefreshMode {
  REFRESH_NONE,
  REFRESH_UPDATED_FILES,
  REFRESH_UPDATED_AND_INCOMPLETE_FILES,
  REFRESH_ALL_FILES
};

struct RefreshInfo {
  std::set<utility::file::FilePath> filesToIndex;
  std::set<utility::file::FilePath> filesToClear;
  std::set<utility::file::FilePath> nonIndexedFilesToClear;

  RefreshMode mode = REFRESH_NONE;
  bool shallow = false;
};