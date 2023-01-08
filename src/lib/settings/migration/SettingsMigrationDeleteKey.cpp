#include "SettingsMigrationDeleteKey.h"

SettingsMigrationDeleteKey::SettingsMigrationDeleteKey(const std::string& key): m_key(key) {}

SettingsMigrationDeleteKey::~SettingsMigrationDeleteKey() = default;

void SettingsMigrationDeleteKey::apply(Settings* migratable) const {
  removeValuesInSettings(migratable, m_key);
}