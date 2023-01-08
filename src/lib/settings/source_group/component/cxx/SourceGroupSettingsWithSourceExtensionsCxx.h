#pragma once

#include "SourceGroupSettingsWithSourceExtensions.h"

class SourceGroupSettingsWithSourceExtensionsCxx : public SourceGroupSettingsWithSourceExtensions {
private:
  std::vector<std::wstring> getDefaultSourceExtensions() const override {
    return {L".c", L".cpp", L".cxx", L".cc"};
  }
};
