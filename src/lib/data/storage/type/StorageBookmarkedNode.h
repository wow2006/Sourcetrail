#ifndef STORAGE_BOOKMARKED_NODE_H
#define STORAGE_BOOKMARKED_NODE_H

#include <string>

#include "types.h"

struct StorageBookmarkedNodeData
{
	StorageBookmarkedNodeData(): bookmarkId(0), serializedNodeName(L"") {}

	StorageBookmarkedNodeData(Id bookmarkId_, const std::wstring& serializedNodeName_)
		: bookmarkId(bookmarkId_), serializedNodeName(serializedNodeName_)
	{
	}

	Id bookmarkId;
	std::wstring serializedNodeName;
};

struct StorageBookmarkedNode: public StorageBookmarkedNodeData
{
	StorageBookmarkedNode(): StorageBookmarkedNodeData(), id(0) {}

	StorageBookmarkedNode(Id id_, const StorageBookmarkedNodeData& data_)
		: StorageBookmarkedNodeData(data_), id(id_)
	{
	}

	StorageBookmarkedNode(Id id_, Id bookmarkId_, const std::wstring& serializedNodeName_)
		: StorageBookmarkedNodeData(bookmarkId_, serializedNodeName_), id(id_)
	{
	}

	Id id;
};

#endif	  // STORAGE_BOOKMARKED_NODE_H
