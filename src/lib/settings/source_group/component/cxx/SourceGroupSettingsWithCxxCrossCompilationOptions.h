#pragma once

#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCxxCrossCompilationOptions : public SourceGroupSettingsComponent {
public:
  static std::vector<std::wstring> getAvailableArchTypes();
  static std::vector<std::wstring> getAvailableVendorTypes();
  static std::vector<std::wstring> getAvailableOsTypes();
  static std::vector<std::wstring> getAvailableEnvironmentTypes();

  virtual ~SourceGroupSettingsWithCxxCrossCompilationOptions() = default;

  bool getTargetOptionsEnabled() const;
  void setTargetOptionsEnabled(bool targetOptionsEnabled);

  std::wstring getTargetArch() const;
  void setTargetArch(const std::wstring& arch);

  std::wstring getTargetVendor() const;
  void setTargetVendor(const std::wstring& vendor);

  std::wstring getTargetSys() const;
  void setTargetSys(const std::wstring& sys);

  std::wstring getTargetAbi() const;
  void setTargetAbi(const std::wstring& abi);

  std::wstring getTargetFlag() const;

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  bool m_targetOptionsEnabled = false;
  std::wstring m_targetArch;
  std::wstring m_targetVendor;
  std::wstring m_targetSys;
  std::wstring m_targetAbi;
};
