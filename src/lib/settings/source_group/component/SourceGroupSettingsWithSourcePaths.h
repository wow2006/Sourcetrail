#pragma once

#include "FilePath.h"
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithSourcePaths : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithSourcePaths() = default;

  std::vector<utility::file::FilePath> getSourcePaths() const;
  std::vector<utility::file::FilePath> getSourcePathsExpandedAndAbsolute() const;
  void setSourcePaths(const std::vector<utility::file::FilePath>& sourcePaths);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  std::vector<utility::file::FilePath> m_sourcePaths;
};
