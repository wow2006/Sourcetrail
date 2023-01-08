#pragma once

#include "SourceGroupSettingsWithCStandard.h"
#include "SourceGroupSettingsWithComponents.h"
#include "SourceGroupSettingsWithCppStandard.h"
#include "SourceGroupSettingsWithCxxCodeblocksPath.h"
#include "SourceGroupSettingsWithCxxPathsAndFlags.h"
#include "SourceGroupSettingsWithExcludeFilters.h"
#include "SourceGroupSettingsWithIndexedHeaderPaths.h"
#include "SourceGroupSettingsWithSourceExtensionsCxx.h"

class SourceGroupSettingsCxxCodeblocks
    : public SourceGroupSettingsWithComponents<SourceGroupSettingsWithCppStandard,
                                               SourceGroupSettingsWithCStandard,
                                               SourceGroupSettingsWithCxxCodeblocksPath,
                                               SourceGroupSettingsWithCxxPathsAndFlags,
                                               SourceGroupSettingsWithExcludeFilters,
                                               SourceGroupSettingsWithIndexedHeaderPaths,
                                               SourceGroupSettingsWithSourceExtensionsCxx> {
public:
  SourceGroupSettingsCxxCodeblocks(const std::string& id, const ProjectSettings* projectSettings)
      : SourceGroupSettingsWithComponents(SOURCE_GROUP_CXX_CODEBLOCKS, id, projectSettings) {}

  std::shared_ptr<SourceGroupSettings> createCopy() const override {
    return std::make_shared<SourceGroupSettingsCxxCodeblocks>(*this);
  }
};
