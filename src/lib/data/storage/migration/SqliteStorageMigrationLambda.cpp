#include "SqliteStorageMigrationLambda.h"


SqliteStorageMigrationLambda::SqliteStorageMigrationLambda(
	std::function<void(const SqliteStorageMigration*, SqliteStorage*)> lambda_)
	: m_lambda(lambda_)
{
}

SqliteStorageMigrationLambda::~SqliteStorageMigrationLambda() {}

void SqliteStorageMigrationLambda::apply(SqliteStorage* migratable) const
{
	m_lambda(this, migratable);
}
