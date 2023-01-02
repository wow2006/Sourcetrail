#ifndef SOURCE_GROUP_SETTINGS_H
#define SOURCE_GROUP_SETTINGS_H

#include <memory>
#include <vector>

#include "LanguageType.h"
#include "SourceGroupSettingsBase.h"
#include "SourceGroupStatusType.h"
#include "SourceGroupType.h"

namespace utility {
class ConfigManager;
}
class FilePath;

class SourceGroupSettings : virtual public SourceGroupSettingsBase {
public:
  static const size_t s_version;
  static const std::string s_keyPrefix;

  SourceGroupSettings(SourceGroupType type,
                      const std::string& id,
                      const ProjectSettings* projectSettings);
  virtual ~SourceGroupSettings() = default;

  virtual std::shared_ptr<SourceGroupSettings> createCopy() const = 0;

  virtual void loadSettings(const utility::ConfigManager* config) = 0;
  virtual void saveSettings(utility::ConfigManager* config) = 0;
  virtual bool equalsSettings(const SourceGroupSettingsBase* other) = 0;

  bool equals(const SourceGroupSettingsBase* other) const;
  void load(const utility::ConfigManager* config, const std::string& key);
  void save(utility::ConfigManager* config, const std::string& key);

  std::string getId() const;
  void setId(const std::string& id);

  SourceGroupType getType() const;
  LanguageType getLanguage() const;

  std::string getName() const;
  void setName(const std::string& name);

  SourceGroupStatusType getStatus() const;
  void setStatus(SourceGroupStatusType status);

  const ProjectSettings* getProjectSettings() const override;
  FilePath getSourceGroupDependenciesDirectoryPath() const override;
  FilePath getProjectDirectoryPath() const;

  std::vector<FilePath> makePathsExpandedAndAbsolute(const std::vector<FilePath>& paths) const;

protected:
  const ProjectSettings* m_projectSettings;

private:
  const SourceGroupType m_type;
  std::string m_id;
  std::string m_name;
  SourceGroupStatusType m_status;
};

#endif    // SOURCE_GROUP_SETTINGS_H
