#include "SourceGroupSettingsWithCxxCdbPath.h"

#include "ProjectSettings.h"
#include "utilityFile.h"

utility::file::FilePath SourceGroupSettingsWithCxxCdbPath::getCompilationDatabasePath() const {
  return m_compilationDatabasePath;
}

utility::file::FilePath SourceGroupSettingsWithCxxCdbPath::getCompilationDatabasePathExpandedAndAbsolute() const {
  return utility::getExpandedAndAbsolutePath(
      getCompilationDatabasePath(), getProjectSettings()->getProjectDirectoryPath());
}

void SourceGroupSettingsWithCxxCdbPath::setCompilationDatabasePath(
    const utility::file::FilePath& compilationDatabasePath) {
  m_compilationDatabasePath = compilationDatabasePath;
}

bool SourceGroupSettingsWithCxxCdbPath::equals(const SourceGroupSettingsBase* other) const {
  const SourceGroupSettingsWithCxxCdbPath* otherPtr =
      dynamic_cast<const SourceGroupSettingsWithCxxCdbPath*>(other);

  return (otherPtr && m_compilationDatabasePath == otherPtr->m_compilationDatabasePath);
}

void SourceGroupSettingsWithCxxCdbPath::load(const utility::ConfigManagerigManager* config,
                                             const std::string& key) {
  setCompilationDatabasePath(
      config->getValueOrDefault(key + "/build_file_path/compilation_db_path", utility::file::FilePath(L"")));
}

void SourceGroupSettingsWithCxxCdbPath::save(utility::ConfigManagerigManager* config,
                                             const std::string& key) {
  config->setValue(key + "/build_file_path/compilation_db_path", getCompilationDatabasePath().wstr());
}
