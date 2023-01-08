#pragma once

#include "FilePath.h"
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithPythonEnvironmentPath : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithPythonEnvironmentPath() = default;

  FilePath getEnvironmentPath() const;
  FilePath getEnvironmentPathExpandedAndAbsolute() const;
  void setEnvironmentPath(const FilePath& environmentPath);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  FilePath m_environmentPath;
};
