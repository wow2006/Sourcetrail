#pragma once

#include "FilePath.h"
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCxxPchOptions : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithCxxPchOptions() = default;

  FilePath getPchDependenciesDirectoryPath() const;

  FilePath getPchInputFilePath() const;
  FilePath getPchInputFilePathExpandedAndAbsolute() const;
  void setPchInputFilePathFilePath(const FilePath& path);

  std::vector<std::wstring> getPchFlags() const;
  void setPchFlags(const std::vector<std::wstring>& pchFlags);

  bool getUseCompilerFlags() const;
  void setUseCompilerFlags(bool useCompilerFlags);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManagerigManager* config, const std::string& key) override;
  void save(utility::ConfigManagerigManager* config, const std::string& key) override;

private:
  FilePath m_pchInputFilePath;
  std::vector<std::wstring> m_pchFlags;
  bool m_useCompilerFlags = true;
};
