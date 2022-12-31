#pragma once
// STL
#include <memory>
#include <vector>

class IndexerComposite;
class LanguagePackage;

class LanguagePackageManager final {
public:
  using Ptr = std::shared_ptr<LanguagePackageManager>;

  static Ptr getInstance();

  static void destroyInstance();

  void addPackage(std::shared_ptr<LanguagePackage> package);

  std::shared_ptr<IndexerComposite> instantiateSupportedIndexers();

private:
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
  static Ptr s_instance;

  LanguagePackageManager() = default;

  std::vector<std::shared_ptr<LanguagePackage>> m_packages;
};
