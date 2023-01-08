#pragma once

#include "SourceGroupSettingsWithComponents.h"
#include "SourceGroupSettingsWithExcludeFilters.h"
#include "SourceGroupSettingsWithJavaMaven.h"
#include "SourceGroupSettingsWithJavaStandard.h"
#include "SourceGroupSettingsWithSourceExtensionsJava.h"

class SourceGroupSettingsJavaMaven
    : public SourceGroupSettingsWithComponents<SourceGroupSettingsWithExcludeFilters,
                                               SourceGroupSettingsWithJavaMaven,
                                               SourceGroupSettingsWithJavaStandard,
                                               SourceGroupSettingsWithSourceExtensionsJava> {
public:
  SourceGroupSettingsJavaMaven(const std::string& id, const ProjectSettings* projectSettings)
      : SourceGroupSettingsWithComponents(SOURCE_GROUP_JAVA_MAVEN, id, projectSettings) {}

  std::shared_ptr<SourceGroupSettings> createCopy() const override {
    return std::make_shared<SourceGroupSettingsJavaMaven>(*this);
  }
};
