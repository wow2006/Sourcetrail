#pragma once

#include "Migration.h"
#include "SqliteStorage.h"

class SqliteStorageMigration : public Migration<SqliteStorage> {
public:
  virtual ~SqliteStorageMigration();

  bool executeStatementInStorage(SqliteStorage* storage, const std::string& statement) const;
};