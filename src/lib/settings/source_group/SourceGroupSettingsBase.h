#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
class ProjectSettings;

class SourceGroupSettingsBase {
public:
  virtual ~SourceGroupSettingsBase() = default;

  virtual const ProjectSettings* getProjectSettings() const = 0;

  virtual utility::file::FilePath getSourceGroupDependenciesDirectoryPath() const = 0;
};
