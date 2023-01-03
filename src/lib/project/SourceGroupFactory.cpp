#include "SourceGroupFactory.h"

#include "SourceGroup.h"
#include "SourceGroupFactoryModule.h"
#include "SourceGroupSettings.h"

std::shared_ptr<SourceGroupFactory> SourceGroupFactory::getInstance() {
  if(!s_instance) {
    s_instance = std::shared_ptr<SourceGroupFactory>(new SourceGroupFactory());
  }
  return s_instance;
}

void SourceGroupFactory::addModule(std::shared_ptr<SourceGroupFactoryModule> module) {
  m_modules.push_back(std::move(module));
}

std::vector<std::shared_ptr<SourceGroup>> SourceGroupFactory::createSourceGroups(
const std::vector<std::shared_ptr<SourceGroupSettings>>& allSourceGroupSettings) {
  std::vector<std::shared_ptr<SourceGroup>> sourceGroups;
  for(const auto& sourceGroupSettings : allSourceGroupSettings) {
    auto sourceGroup = createSourceGroup(sourceGroupSettings);
    if(sourceGroup) {
      sourceGroups.push_back(std::move(sourceGroup));
    }
  }
  return sourceGroups;
}

std::shared_ptr<SourceGroup> SourceGroupFactory::createSourceGroup(const std::shared_ptr<SourceGroupSettings>& settings) {
  std::shared_ptr<SourceGroup> sourceGroup;

  for(const auto& module : m_modules) {
    if(module->supports(settings->getType())) {
      sourceGroup = module->createSourceGroup(settings);
      break;
    }
  }

  return sourceGroup;
}

std::shared_ptr<SourceGroupFactory> SourceGroupFactory::s_instance;

SourceGroupFactory::SourceGroupFactory() = default;