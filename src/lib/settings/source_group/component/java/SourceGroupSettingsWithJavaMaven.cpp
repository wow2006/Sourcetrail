#include "SourceGroupSettingsWithJavaMaven.h"

#include "ConfigManager.h"
#include "ProjectSettings.h"
#include "utilityFile.h"

utility::file::FilePath SourceGroupSettingsWithJavaMaven::getMavenDependenciesDirectoryPath() const {
  return getSourceGroupDependenciesDirectoryPath().concatenate(L"maven");
}

utility::file::FilePath SourceGroupSettingsWithJavaMaven::getMavenProjectFilePath() const {
  return m_mavenProjectFilePath;
}

utility::file::FilePath SourceGroupSettingsWithJavaMaven::getMavenProjectFilePathExpandedAndAbsolute() const {
  return utility::getExpandedAndAbsolutePath(
      getMavenProjectFilePath(), getProjectSettings()->getProjectDirectoryPath());
}

void SourceGroupSettingsWithJavaMaven::setMavenProjectFilePath(const utility::file::FilePath& path) {
  m_mavenProjectFilePath = path;
}

bool SourceGroupSettingsWithJavaMaven::getShouldIndexMavenTests() const {
  return m_shouldIndexMavenTests;
}

void SourceGroupSettingsWithJavaMaven::setShouldIndexMavenTests(bool value) {
  m_shouldIndexMavenTests = value;
}

utility::file::FilePath SourceGroupSettingsWithJavaMaven::getMavenSettingsFilePath() const {
  return m_mavenSettingsFilePath;
}

utility::file::FilePath SourceGroupSettingsWithJavaMaven::getMavenSettingsFilePathExpandedAndAbsolute() const {
  return utility::getExpandedAndAbsolutePath(
      getMavenSettingsFilePath(), getProjectSettings()->getProjectDirectoryPath());
}

void SourceGroupSettingsWithJavaMaven::setMavenSettingsFilePath(const utility::file::FilePath& path) {
  m_mavenSettingsFilePath = path;
}

bool SourceGroupSettingsWithJavaMaven::equals(const SourceGroupSettingsBase* other) const {
  const SourceGroupSettingsWithJavaMaven* otherPtr =
      dynamic_cast<const SourceGroupSettingsWithJavaMaven*>(other);

  return (otherPtr && m_mavenProjectFilePath == otherPtr->m_mavenProjectFilePath && otherPtr &&
          m_mavenSettingsFilePath == otherPtr->m_mavenSettingsFilePath &&
          m_shouldIndexMavenTests == otherPtr->m_shouldIndexMavenTests);
}

void SourceGroupSettingsWithJavaMaven::load(const utility::ConfigManager* config,
                                            const std::string& key) {
  setMavenProjectFilePath(config->getValueOrDefault(key + "/maven/project_file_path", utility::file::FilePath(L"")));
  setMavenSettingsFilePath(
      config->getValueOrDefault(key + "/maven/settings_file_path", utility::file::FilePath(L"")));
  setShouldIndexMavenTests(config->getValueOrDefault(key + "/maven/should_index_tests", false));
}

void SourceGroupSettingsWithJavaMaven::save(utility::ConfigManager* config, const std::string& key) {
  config->setValue(key + "/maven/project_file_path", getMavenProjectFilePath().wstr());
  config->setValue(key + "/maven/settings_file_path", getMavenSettingsFilePath().wstr());
  config->setValue(key + "/maven/should_index_tests", getShouldIndexMavenTests());
}
