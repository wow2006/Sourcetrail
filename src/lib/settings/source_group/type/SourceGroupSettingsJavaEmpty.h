#pragma once

#include "SourceGroupSettingsWithClasspath.h"
#include "SourceGroupSettingsWithComponents.h"
#include "SourceGroupSettingsWithExcludeFilters.h"
#include "SourceGroupSettingsWithJavaStandard.h"
#include "SourceGroupSettingsWithSourceExtensionsJava.h"
#include "SourceGroupSettingsWithSourcePaths.h"

class SourceGroupSettingsJavaEmpty
    : public SourceGroupSettingsWithComponents<SourceGroupSettingsWithClasspath,
                                               SourceGroupSettingsWithExcludeFilters,
                                               SourceGroupSettingsWithJavaStandard,
                                               SourceGroupSettingsWithSourceExtensionsJava,
                                               SourceGroupSettingsWithSourcePaths> {
public:
  SourceGroupSettingsJavaEmpty(const std::string& id, const ProjectSettings* projectSettings)
      : SourceGroupSettingsWithComponents(SOURCE_GROUP_JAVA_EMPTY, id, projectSettings) {}

  std::shared_ptr<SourceGroupSettings> createCopy() const override {
    return std::make_shared<SourceGroupSettingsJavaEmpty>(*this);
  }
};
