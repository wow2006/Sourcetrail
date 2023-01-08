#pragma once

#include "SettingsMigration.h"

class SettingsMigrationLambda: public SettingsMigration
{
public:
	SettingsMigrationLambda(std::function<void(const SettingsMigration*, Settings*)> lambda);
	~SettingsMigrationLambda() override;
	virtual void apply(Settings* migratable) const;

private:
	std::function<void(const SettingsMigration*, Settings*)> m_lambda;
};