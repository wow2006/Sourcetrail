#pragma once

#include "LanguageType.h"
#include "Settings.h"
#include "SettingsMigrator.h"

class SourceGroupSettings;

class ProjectSettings : public Settings {
public:
  static const std::wstring PROJECT_FILE_EXTENSION;
  static const std::wstring BOOKMARK_DB_FILE_EXTENSION;
  static const std::wstring INDEX_DB_FILE_EXTENSION;
  static const std::wstring TEMP_INDEX_DB_FILE_EXTENSION;

  static const size_t VERSION;
  static LanguageType getLanguageOfProject(const utility::file::FilePath& filePath);

  ProjectSettings();
  ProjectSettings(const utility::file::FilePath& projectFilePath);
  virtual ~ProjectSettings();

  bool equalsExceptNameAndLocation(const ProjectSettings& other) const;

  bool needMigration() const;
  void migrate();

  bool reload();

  utility::file::FilePath getProjectFilePath() const;
  void setProjectFilePath(std::wstring projectName, const utility::file::FilePath& projectFileLocation);
  utility::file::FilePath getDependenciesDirectoryPath() const;

  utility::file::FilePath getDBFilePath() const;
  utility::file::FilePath getTempDBFilePath() const;
  utility::file::FilePath getBookmarkDBFilePath() const;

  std::wstring getProjectName() const;
  utility::file::FilePath getProjectDirectoryPath() const;

  std::string getDescription() const;

  std::vector<std::shared_ptr<SourceGroupSettings>> getAllSourceGroupSettings() const;
  void setAllSourceGroupSettings(const std::vector<std::shared_ptr<SourceGroupSettings>>& allSettings);

  std::vector<utility::file::FilePath> makePathsExpandedAndAbsolute(const std::vector<utility::file::FilePath>& paths) const;
  utility::file::FilePath makePathExpandedAndAbsolute(const utility::file::FilePath& path) const;

private:
  SettingsMigrator getMigrations() const;
};
