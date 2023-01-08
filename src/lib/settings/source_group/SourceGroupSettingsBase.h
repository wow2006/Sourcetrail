#pragma once

class FilePath;
class ProjectSettings;

class SourceGroupSettingsBase {
public:
  virtual ~SourceGroupSettingsBase() = default;

  virtual const ProjectSettings* getProjectSettings() const = 0;

  virtual FilePath getSourceGroupDependenciesDirectoryPath() const = 0;
};
