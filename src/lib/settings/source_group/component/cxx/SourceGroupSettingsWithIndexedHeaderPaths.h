#pragma once

#include "SourceGroupSettingsComponent.h"

namespace utility::file {
class FilePath;
} // namespace class utility::file

class SourceGroupSettingsWithIndexedHeaderPaths : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithIndexedHeaderPaths() = default;

  std::vector<utility::file::FilePath> getIndexedHeaderPaths() const;
  std::vector<utility::file::FilePath> getIndexedHeaderPathsExpandedAndAbsolute() const;
  void setIndexedHeaderPaths(const std::vector<utility::file::FilePath>& indexedHeaderPaths);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  std::vector<utility::file::FilePath> m_indexedHeaderPaths;
};
