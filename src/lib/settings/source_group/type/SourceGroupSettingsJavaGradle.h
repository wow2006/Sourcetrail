#pragma once

#include "SourceGroupSettingsWithComponents.h"
#include "SourceGroupSettingsWithExcludeFilters.h"
#include "SourceGroupSettingsWithJavaGradle.h"
#include "SourceGroupSettingsWithJavaStandard.h"
#include "SourceGroupSettingsWithSourceExtensionsJava.h"

class SourceGroupSettingsJavaGradle
    : public SourceGroupSettingsWithComponents<SourceGroupSettingsWithExcludeFilters,
                                               SourceGroupSettingsWithJavaGradle,
                                               SourceGroupSettingsWithJavaStandard,
                                               SourceGroupSettingsWithSourceExtensionsJava> {
public:
  SourceGroupSettingsJavaGradle(const std::string& id, const ProjectSettings* projectSettings)
      : SourceGroupSettingsWithComponents(SOURCE_GROUP_JAVA_GRADLE, id, projectSettings) {}

  std::shared_ptr<SourceGroupSettings> createCopy() const override {
    return std::make_shared<SourceGroupSettingsJavaGradle>(*this);
  }
};
