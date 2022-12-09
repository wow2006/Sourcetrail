#ifndef SOURCE_GROUP_SETTINGS_BASE_H
#define SOURCE_GROUP_SETTINGS_BASE_H

class FilePath;
class ProjectSettings;

class SourceGroupSettingsBase {
 public:
  virtual ~SourceGroupSettingsBase() = default;

  virtual const ProjectSettings* getProjectSettings() const = 0;
  virtual FilePath getSourceGroupDependenciesDirectoryPath() const = 0;
};

#endif  // SOURCE_GROUP_SETTINGS_BASE_H
