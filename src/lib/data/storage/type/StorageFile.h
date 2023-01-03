#ifndef STORAGE_FILE_H
#define STORAGE_FILE_H

#include <string>

#include "types.h"

struct StorageFile
{
	StorageFile()
		: id(0)
		, filePath(L"")
		, languageIdentifier(L"")
		, modificationTime("")
		, indexed(true)
		, complete(true)
	{
	}

	StorageFile(
		Id id_,
		std::wstring filePath_,
		std::wstring languageIdentifier_,
		std::string modificationTime_,
		bool indexed_,
		bool complete_)
		: id(id_)
		, filePath(std::move(filePath_))
		, languageIdentifier(std::move(languageIdentifier_))
		, modificationTime(std::move(modificationTime_))
		, indexed(indexed_)
		, complete(complete_)
	{
	}

	bool operator<(const StorageFile& other) const
	{
		return filePath < other.filePath;
	}

	Id id;
	std::wstring filePath;
	std::wstring languageIdentifier;
	std::string modificationTime;
	bool indexed;
	bool complete;
};

#endif	  // STORAGE_FILE_H
