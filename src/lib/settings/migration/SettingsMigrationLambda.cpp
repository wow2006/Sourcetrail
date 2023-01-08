#include "SettingsMigrationLambda.h"

SettingsMigrationLambda::SettingsMigrationLambda(
    std::function<void(const SettingsMigration*, Settings*)> lambda)
    : m_lambda(std::move(lambda)) {}

SettingsMigrationLambda::~SettingsMigrationLambda() = default;

void SettingsMigrationLambda::apply(Settings* migratable) const {
  m_lambda(this, migratable);
}
