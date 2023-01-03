#ifndef STORAGE_BOOKMARK_CATEGORY_H
#define STORAGE_BOOKMARK_CATEGORY_H

#include <string>

#include "types.h"

struct StorageBookmarkCategoryData
{
	StorageBookmarkCategoryData(): name(L"") {}

	StorageBookmarkCategoryData(const std::wstring& name_): name(name_) {}

	std::wstring name;
};

struct StorageBookmarkCategory: public StorageBookmarkCategoryData
{
	StorageBookmarkCategory(): StorageBookmarkCategoryData(), id(0) {}

	StorageBookmarkCategory(Id id_, const StorageBookmarkCategoryData& data_)
		: StorageBookmarkCategoryData(data_), id(id_)
	{
	}

	StorageBookmarkCategory(Id id_, const std::wstring& name_)
		: StorageBookmarkCategoryData(name_), id(id_)
	{
	}

	Id id;
};

#endif	  // STORAGE_BOOKMARK_CATEGORY_H
