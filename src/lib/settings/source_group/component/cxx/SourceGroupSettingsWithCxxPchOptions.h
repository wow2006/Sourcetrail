#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCxxPchOptions : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithCxxPchOptions() = default;

  utility::file::FilePath getPchDependenciesDirectoryPath() const;

  utility::file::FilePath getPchInputFilePath() const;
  utility::file::FilePath getPchInputFilePathExpandedAndAbsolute() const;
  void setPchInputFilePathFilePath(const utility::file::FilePath& path);

  std::vector<std::wstring> getPchFlags() const;
  void setPchFlags(const std::vector<std::wstring>& pchFlags);

  bool getUseCompilerFlags() const;
  void setUseCompilerFlags(bool useCompilerFlags);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManagerigManager* config, const std::string& key) override;
  void save(utility::ConfigManagerigManager* config, const std::string& key) override;

private:
  utility::file::FilePath m_pchInputFilePath;
  std::vector<std::wstring> m_pchFlags;
  bool m_useCompilerFlags = true;
};
