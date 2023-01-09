#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCxxCodeblocksPath : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithCxxCodeblocksPath() = default;

  utility::file::FilePath getCodeblocksProjectPath() const;
  utility::file::FilePath getCodeblocksProjectPathExpandedAndAbsolute() const;
  void setCodeblocksProjectPath(const utility::file::FilePath& codeblocksProjectPath);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  utility::file::FilePath m_codeblocksProjectPath;
};
