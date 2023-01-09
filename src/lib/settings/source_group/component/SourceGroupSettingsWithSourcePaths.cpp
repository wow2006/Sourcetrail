#include "SourceGroupSettingsWithSourcePaths.h"

#include "ProjectSettings.h"
#include "utility.h"

std::vector<utility::file::FilePath> SourceGroupSettingsWithSourcePaths::getSourcePaths() const {
  return m_sourcePaths;
}

std::vector<utility::file::FilePath> SourceGroupSettingsWithSourcePaths::getSourcePathsExpandedAndAbsolute() const {
  return getProjectSettings()->makePathsExpandedAndAbsolute(getSourcePaths());
}

void SourceGroupSettingsWithSourcePaths::setSourcePaths(const std::vector<utility::file::FilePath>& sourcePaths) {
  m_sourcePaths = sourcePaths;
}

bool SourceGroupSettingsWithSourcePaths::equals(const SourceGroupSettingsBase* other) const {
  const SourceGroupSettingsWithSourcePaths* otherPtr =
      dynamic_cast<const SourceGroupSettingsWithSourcePaths*>(other);

  return (otherPtr && utility::isPermutation(m_sourcePaths, otherPtr->m_sourcePaths));
}

void SourceGroupSettingsWithSourcePaths::load(const utility::ConfigManager* config,
                                              const std::string& key) {
  setSourcePaths(
      config->getValuesOrDefaults(key + "/source_paths/source_path", std::vector<utility::file::FilePath>()));
}

void SourceGroupSettingsWithSourcePaths::save(utility::ConfigManager* config, const std::string& key) {
  config->setValues(key + "/source_paths/source_path", getSourcePaths());
}
