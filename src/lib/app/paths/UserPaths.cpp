#include "UserPaths.h"

#include <string>


FilePath s_userDataDirectoryPath;

namespace userPaths {

FilePath getUserDataDirectoryPath() { return s_userDataDirectoryPath; }

void setUserDataDirectoryPath(const FilePath& path) { s_userDataDirectoryPath = path; }

FilePath getAppSettingsFilePath() {
  return getUserDataDirectoryPath().concatenate(L"ApplicationSettings.xml");
}

FilePath getWindowSettingsFilePath() {
  return getUserDataDirectoryPath().concatenate(L"window_settings.ini");
}

FilePath getLogDirectoryPath() { return getUserDataDirectoryPath().concatenate(L"log/"); }


}