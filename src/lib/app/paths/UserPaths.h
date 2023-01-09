#pragma once
#include "FilePath.h"

class UserPaths {
public:
  static utility::file::FilePath getUserDataDirectoryPath();
  static void setUserDataDirectoryPath(const utility::file::FilePath& path);

  static utility::file::FilePath getAppSettingsFilePath();
  static utility::file::FilePath getWindowSettingsFilePath();
  static utility::file::FilePath getLogDirectoryPath();

private:
  static utility::file::FilePath s_userDataDirectoryPath;
};