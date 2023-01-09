#include "UserPaths.h"

utility::file::FilePath UserPaths::s_userDataDirectoryPath;

utility::file::FilePath UserPaths::getUserDataDirectoryPath() {
  return s_userDataDirectoryPath;
}

void UserPaths::setUserDataDirectoryPath(const utility::file::FilePath& path) {
  s_userDataDirectoryPath = path;
}

utility::file::FilePath UserPaths::getAppSettingsFilePath() {
  return getUserDataDirectoryPath().concatenate(L"ApplicationSettings.xml");
}

utility::file::FilePath UserPaths::getWindowSettingsFilePath() {
  return getUserDataDirectoryPath().concatenate(L"window_settings.ini");
}

utility::file::FilePath UserPaths::getLogDirectoryPath() {
  return getUserDataDirectoryPath().concatenate(L"log/");
}
