#ifndef STORAGE_LOCAL_SYMBOL_H
#define STORAGE_LOCAL_SYMBOL_H

#include <string>

#include "types.h"

struct StorageLocalSymbolData
{
	StorageLocalSymbolData(): name(L"") {}

	StorageLocalSymbolData(std::wstring name_): name(std::move(name_)) {}

	bool operator<(const StorageLocalSymbolData& other) const
	{
		return name < other.name;
	}

	std::wstring name;
};

struct StorageLocalSymbol: public StorageLocalSymbolData
{
	StorageLocalSymbol(): StorageLocalSymbolData(), id(0) {}

	StorageLocalSymbol(Id id_, const StorageLocalSymbolData& data_)
		: StorageLocalSymbolData(data_), id(id_)
	{
	}

	StorageLocalSymbol(Id id_, std::wstring name_): StorageLocalSymbolData(std::move(name_)), id(id_) {}

	Id id;
};

#endif	  // STORAGE_LOCAL_SYMBOL_H
