#pragma once

#include "SqliteStorageMigration.h"

class SqliteStorageMigrationLambda : public SqliteStorageMigration {
public:
  SqliteStorageMigrationLambda(std::function<void(const SqliteStorageMigration*, SqliteStorage*)> lambda);
  virtual ~SqliteStorageMigrationLambda();
  virtual void apply(SqliteStorage* migratable) const;

private:
  std::function<void(const SqliteStorageMigration*, SqliteStorage*)> m_lambda;
};