#include "SettingsMigrationLambda.h"

SettingsMigrationLambda::SettingsMigrationLambda(
	std::function<void(const SettingsMigration*, Settings*)> lambda)
	: m_lambda(lambda)
{
}

SettingsMigrationLambda::~SettingsMigrationLambda() {}

void SettingsMigrationLambda::apply(Settings* migratable) const
{
	m_lambda(this, migratable);
}
