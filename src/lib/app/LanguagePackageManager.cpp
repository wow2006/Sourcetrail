#include "LanguagePackageManager.h"

#include "IndexerComposite.h"
#include "LanguagePackage.h"

std::shared_ptr<LanguagePackageManager> LanguagePackageManager::getInstance() {
  if (!s_instance) {
    s_instance = std::shared_ptr<LanguagePackageManager>(new LanguagePackageManager());
  }
  return s_instance;
}

void LanguagePackageManager::destroyInstance() { s_instance.reset(); }

void LanguagePackageManager::addPackage(std::shared_ptr<LanguagePackage> package) { m_packages.emplace_back(package); }

std::shared_ptr<IndexerComposite> LanguagePackageManager::instantiateSupportedIndexers() {
  auto composite = std::make_shared<IndexerComposite>();
  for (const auto& package : m_packages) {
    for (const auto& indexer : package->instantiateSupportedIndexers()) {
      composite->addIndexer(indexer);
    }
  }
  return composite;
}

std::shared_ptr<LanguagePackageManager> LanguagePackageManager::s_instance;
