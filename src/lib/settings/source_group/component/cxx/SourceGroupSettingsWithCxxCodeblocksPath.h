#pragma once

#include "FilePath.h"
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCxxCodeblocksPath : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithCxxCodeblocksPath() = default;

  FilePath getCodeblocksProjectPath() const;
  FilePath getCodeblocksProjectPathExpandedAndAbsolute() const;
  void setCodeblocksProjectPath(const FilePath& codeblocksProjectPath);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  FilePath m_codeblocksProjectPath;
};
