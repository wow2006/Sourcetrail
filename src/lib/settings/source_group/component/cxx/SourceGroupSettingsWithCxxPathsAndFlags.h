#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCxxPathsAndFlags : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithCxxPathsAndFlags() = default;

  std::vector<utility::file::FilePath> getHeaderSearchPaths() const;
  std::vector<utility::file::FilePath> getHeaderSearchPathsExpandedAndAbsolute() const;
  void setHeaderSearchPaths(const std::vector<utility::file::FilePath>& headerSearchPaths);

  std::vector<utility::file::FilePath> getFrameworkSearchPaths() const;
  std::vector<utility::file::FilePath> getFrameworkSearchPathsExpandedAndAbsolute() const;
  void setFrameworkSearchPaths(const std::vector<utility::file::FilePath>& frameworkSearchPaths);

  std::vector<std::wstring> getCompilerFlags() const;
  void setCompilerFlags(const std::vector<std::wstring>& compilerFlags);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::utility::ConfigManagerigManager* config, const std::string& key) override;
  void save(utility::utility::ConfigManagerigManager* config, const std::string& key) override;

private:
  std::vector<utility::file::FilePath> m_headerSearchPaths;
  std::vector<utility::file::FilePath> m_frameworkSearchPaths;
  std::vector<std::wstring> m_compilerFlags;
};
