#pragma once

class SourceGroup;
class SourceGroupSettings;
class SourceGroupFactoryModule;

class SourceGroupFactory {
public:
  static std::shared_ptr<SourceGroupFactory> getInstance();

  void addModule(std::shared_ptr<SourceGroupFactoryModule> module);

  std::vector<std::shared_ptr<SourceGroup>> createSourceGroups(
      const std::vector<std::shared_ptr<SourceGroupSettings>>& allSourceGroupSettings);

  std::shared_ptr<SourceGroup> createSourceGroup(const std::shared_ptr<SourceGroupSettings>& settings);

private:
  static std::shared_ptr<SourceGroupFactory> s_instance;
  SourceGroupFactory();

  std::vector<std::shared_ptr<SourceGroupFactoryModule>> m_modules;
};