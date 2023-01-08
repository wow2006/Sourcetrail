#pragma once

#include "SettingsMigration.h"

class SettingsMigrationMoveKey : public SettingsMigration {
public:
  SettingsMigrationMoveKey(const std::string& oldKey, const std::string& newKey);
  ~SettingsMigrationMoveKey() override;
  virtual void apply(Settings* migratable) const;

private:
  const std::string m_oldKey;
  const std::string m_newKey;
};