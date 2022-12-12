#pragma once

#include "FilePath.hpp"

namespace userPaths {
  FilePath getUserDataDirectoryPath();
  void setUserDataDirectoryPath(const FilePath& path);
  FilePath getAppSettingsFilePath();
  FilePath getWindowSettingsFilePath();
  FilePath getLogDirectoryPath();
};
