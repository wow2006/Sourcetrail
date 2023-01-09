#include "SourceGroupSettingsWithIndexedHeaderPaths.h"

#include "ProjectSettings.h"
#include "utility.h"

std::vector<utility::file::FilePath> SourceGroupSettingsWithIndexedHeaderPaths::getIndexedHeaderPaths() const {
  return m_indexedHeaderPaths;
}

std::vector<utility::file::FilePath> SourceGroupSettingsWithIndexedHeaderPaths::getIndexedHeaderPathsExpandedAndAbsolute()
    const {
  return getProjectSettings()->makePathsExpandedAndAbsolute(getIndexedHeaderPaths());
}

void SourceGroupSettingsWithIndexedHeaderPaths::setIndexedHeaderPaths(
    const std::vector<utility::file::FilePath>& indexedHeaderPaths) {
  m_indexedHeaderPaths = indexedHeaderPaths;
}

bool SourceGroupSettingsWithIndexedHeaderPaths::equals(const SourceGroupSettingsBase* other) const {
  const SourceGroupSettingsWithIndexedHeaderPaths* otherPtr =
      dynamic_cast<const SourceGroupSettingsWithIndexedHeaderPaths*>(other);

  return (otherPtr && utility::isPermutation(m_indexedHeaderPaths, otherPtr->m_indexedHeaderPaths));
}

void SourceGroupSettingsWithIndexedHeaderPaths::load(
    const utility::ConfigManagerigManagerigManager* config, const std::string& key) {
  setIndexedHeaderPaths(config->getValuesOrDefaults(
      key + "/indexed_header_paths/indexed_header_path", std::vector<utility::file::FilePath>()));
}

void SourceGroupSettingsWithIndexedHeaderPaths::save(utility::ConfigManagerigManagerigManager* config,
                                                     const std::string& key) {
  config->setValues(key + "/indexed_header_paths/indexed_header_path", getIndexedHeaderPaths());
}
