#pragma once

#include "SourceGroupFactoryModule.h"

class SourceGroupFactoryModuleCustom : public SourceGroupFactoryModule {
public:
  bool supports(SourceGroupType type) const override;

  std::shared_ptr<SourceGroup> createSourceGroup(
      std::shared_ptr<SourceGroupSettings> settings) const override;
};