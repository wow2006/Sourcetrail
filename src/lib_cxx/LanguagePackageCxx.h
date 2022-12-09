#pragma once
// STL
#include <memory>
#include <vector>

#include "LanguagePackage.h"

class LanguagePackageCxx : public LanguagePackage {
 public:
  using IndexerBasePtr = std::shared_ptr<IndexerBase>;

  [[nodiscard]] std::vector<IndexerBasePtr> instantiateSupportedIndexers() const override;
};
