#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithPythonEnvironmentPath : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithPythonEnvironmentPath() = default;

  utility::file::FilePath getEnvironmentPath() const;
  utility::file::FilePath getEnvironmentPathExpandedAndAbsolute() const;
  void setEnvironmentPath(const utility::file::FilePath& environmentPath);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  utility::file::FilePath m_environmentPath;
};
