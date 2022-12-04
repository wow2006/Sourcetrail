#pragma once

#include "SourceGroupFactoryModule.h"

class SourceGroupFactoryModuleCxx : public SourceGroupFactoryModule {
 public:
  bool supports(SourceGroupType type) const override;

  [[nodiscard]] std::shared_ptr<SourceGroup> createSourceGroup(std::shared_ptr<SourceGroupSettings> settings) const override;

};
