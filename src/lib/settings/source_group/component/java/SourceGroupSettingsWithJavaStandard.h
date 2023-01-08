#pragma once

#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithJavaStandard : public SourceGroupSettingsComponent {
public:
  static std::wstring getDefaultJavaStandardStatic();

  virtual ~SourceGroupSettingsWithJavaStandard() = default;

  std::wstring getJavaStandard() const;
  void setJavaStandard(const std::wstring& standard);

  std::vector<std::wstring> getAvailableJavaStandards() const;

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  std::wstring getDefaultJavaStandard() const;

  std::wstring m_javaStandard;
};
