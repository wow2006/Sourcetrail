#pragma once

#include "SourceGroupSettingsWithSourceExtensions.h"

class SourceGroupSettingsWithSourceExtensionsCpp : public SourceGroupSettingsWithSourceExtensions {
private:
  std::vector<std::wstring> getDefaultSourceExtensions() const override {
    return {L".cpp", L".cxx", L".cc"};
  }
};
