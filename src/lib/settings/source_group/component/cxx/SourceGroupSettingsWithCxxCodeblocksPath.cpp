#include "SourceGroupSettingsWithCxxCodeblocksPath.h"

#include "ProjectSettings.h"
#include "utilityFile.h"

utility::file::FilePath SourceGroupSettingsWithCxxCodeblocksPath::getCodeblocksProjectPath() const {
  return m_codeblocksProjectPath;
}

utility::file::FilePath SourceGroupSettingsWithCxxCodeblocksPath::getCodeblocksProjectPathExpandedAndAbsolute() const {
  return utility::getExpandedAndAbsolutePath(
      getCodeblocksProjectPath(), getProjectSettings()->getProjectDirectoryPath());
}

void SourceGroupSettingsWithCxxCodeblocksPath::setCodeblocksProjectPath(
    const utility::file::FilePath& codeblocksProjectPath) {
  m_codeblocksProjectPath = codeblocksProjectPath;
}

bool SourceGroupSettingsWithCxxCodeblocksPath::equals(const SourceGroupSettingsBase* other) const {
  const SourceGroupSettingsWithCxxCodeblocksPath* otherPtr =
      dynamic_cast<const SourceGroupSettingsWithCxxCodeblocksPath*>(other);

  return (otherPtr && m_codeblocksProjectPath == otherPtr->m_codeblocksProjectPath);
}

void SourceGroupSettingsWithCxxCodeblocksPath::load(const utility::ConfigManager* config,
                                                    const std::string& key) {
  setCodeblocksProjectPath(config->getValueOrDefault(key + "/codeblocks_project_path", utility::file::FilePath(L"")));
}

void SourceGroupSettingsWithCxxCodeblocksPath::save(utility::ConfigManager* config,
                                                    const std::string& key) {
  config->setValue(key + "/codeblocks_project_path", getCodeblocksProjectPath().wstr());
}
