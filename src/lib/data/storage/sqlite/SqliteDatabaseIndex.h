#pragma once

#include "CppSQLite3.h"

class SqliteDatabaseIndex
{
public:
	SqliteDatabaseIndex(std::string indexName, std::string indexTarget);

	[[nodiscard]] std::string getName() const;

	void createOnDatabase(CppSQLite3DB& database);
	void removeFromDatabase(CppSQLite3DB& database);

private:
	std::string m_indexName;
	std::string m_indexTarget;
};