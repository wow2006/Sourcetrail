#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithJavaGradle : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithJavaGradle() = default;

  utility::file::FilePath getGradleDependenciesDirectoryPath() const;

  utility::file::FilePath getGradleProjectFilePath() const;
  utility::file::FilePath getGradleProjectFilePathExpandedAndAbsolute() const;
  void setGradleProjectFilePath(const utility::file::FilePath& path);

  bool getShouldIndexGradleTests() const;
  void setShouldIndexGradleTests(bool value);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  utility::file::FilePath m_gradleProjectFilePath;
  bool m_shouldIndexGradleTests = false;
};
