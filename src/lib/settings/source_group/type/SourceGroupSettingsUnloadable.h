#pragma once

#include "SourceGroupSettings.h"

class SourceGroupSettingsUnloadable : public SourceGroupSettings {
public:
  SourceGroupSettingsUnloadable(const std::string& id, const ProjectSettings* projectSettings);
  std::string getTypeString();
  std::shared_ptr<SourceGroupSettings> createCopy() const override;
  void loadSettings(const utility::ConfigManager* config) override;
  void saveSettings(utility::ConfigManager* config) override;
  bool equalsSettings(const SourceGroupSettingsBase* other) override;

private:
  std::string m_typeString;
  std::map<std::string, std::vector<std::string>> m_content;
};
