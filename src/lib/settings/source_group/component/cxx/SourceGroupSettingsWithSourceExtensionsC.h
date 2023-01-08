#pragma once

#include "SourceGroupSettingsWithSourceExtensions.h"

class SourceGroupSettingsWithSourceExtensionsC : public SourceGroupSettingsWithSourceExtensions {
private:
  std::vector<std::wstring> getDefaultSourceExtensions() const override {
    return {L".c"};
  }
};
