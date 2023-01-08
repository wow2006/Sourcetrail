#pragma once

#include "SourceGroupSettingsWithSourceExtensions.h"

class SourceGroupSettingsWithSourceExtensionsEmpty : public SourceGroupSettingsWithSourceExtensions {
private:
  std::vector<std::wstring> getDefaultSourceExtensions() const override {
    return {};
  }
};
