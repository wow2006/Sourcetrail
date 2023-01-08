#pragma once

#include "SettingsMigration.h"

class SettingsMigrationDeleteKey : public SettingsMigration {
public:
  SettingsMigrationDeleteKey(const std::string& key);
  ~SettingsMigrationDeleteKey() override;
  virtual void apply(Settings* migratable) const;

private:
  const std::string m_key;
};