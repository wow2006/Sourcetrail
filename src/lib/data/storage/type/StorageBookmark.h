#ifndef STORAGE_BOOKMARK_H
#define STORAGE_BOOKMARK_H

#include <string>

#include "types.h"

struct StorageBookmarkData
{
	StorageBookmarkData(): name(L""), comment(L""), timestamp(""), categoryId(0) {}

	StorageBookmarkData(
		const std::wstring& name_,
		const std::wstring& comment_,
		const std::string& timestamp_,
		const Id categoryId_)
		: name(name_), comment(comment_), timestamp(timestamp_), categoryId(categoryId_)
	{
	}

	std::wstring name;
	std::wstring comment;
	std::string timestamp;
	Id categoryId;
};

struct StorageBookmark: public StorageBookmarkData
{
	StorageBookmark(): StorageBookmarkData(), id(0) {}

	StorageBookmark(Id id_, const StorageBookmarkData& data_): StorageBookmarkData(data_), id(id_) {}

	StorageBookmark(
		Id id_,
		const std::wstring& name_,
		const std::wstring& comment_,
		const std::string& timestamp_,
		const Id categoryId_)
		: StorageBookmarkData(name_, comment_, timestamp_, categoryId_), id(id_)
	{
	}

	Id id;
};

#endif	  // STORAGE_BOOKMARK_H
