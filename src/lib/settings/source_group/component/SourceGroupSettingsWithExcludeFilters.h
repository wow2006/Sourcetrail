#pragma once

#include "SourceGroupSettingsComponent.h"

namespace utility {
class ConfigManager;
namespace file {
class FilePathFilter;
}}

class SourceGroupSettingsWithExcludeFilters : public SourceGroupSettingsComponent {
public:
  ~SourceGroupSettingsWithExcludeFilters() override;

  std::vector<std::wstring> getExcludeFilterStrings() const;

  std::vector<utility::file::FilePathFilter> getExcludeFiltersExpandedAndAbsolute() const;

  void setExcludeFilterStrings(const std::vector<std::wstring>& excludeFilters);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  std::vector<utility::file::FilePathFilter> getFiltersExpandedAndAbsolute(
      const std::vector<std::wstring>& filterStrings) const;

  std::vector<std::wstring> m_excludeFilters;
};
