#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithJavaMaven : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithJavaMaven() = default;

  utility::file::FilePath getMavenDependenciesDirectoryPath() const;

  utility::file::FilePath getMavenProjectFilePath() const;
  utility::file::FilePath getMavenProjectFilePathExpandedAndAbsolute() const;
  void setMavenProjectFilePath(const utility::file::FilePath& path);

  bool getShouldIndexMavenTests() const;
  void setShouldIndexMavenTests(bool value);

  utility::file::FilePath getMavenSettingsFilePath() const;
  utility::file::FilePath getMavenSettingsFilePathExpandedAndAbsolute() const;
  void setMavenSettingsFilePath(const utility::file::FilePath& path);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  utility::file::FilePath m_mavenProjectFilePath;
  bool m_shouldIndexMavenTests = false;
  utility::file::FilePath m_mavenSettingsFilePath;
};
