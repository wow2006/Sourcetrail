#pragma once

#include "SourceGroupSettingsComponent.h"

class FilePath;

class SourceGroupSettingsWithIndexedHeaderPaths : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithIndexedHeaderPaths() = default;

  std::vector<FilePath> getIndexedHeaderPaths() const;
  std::vector<FilePath> getIndexedHeaderPathsExpandedAndAbsolute() const;
  void setIndexedHeaderPaths(const std::vector<FilePath>& indexedHeaderPaths);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  std::vector<FilePath> m_indexedHeaderPaths;
};
