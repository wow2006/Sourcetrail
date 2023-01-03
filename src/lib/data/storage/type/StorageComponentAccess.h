#ifndef STORAGE_COMPONENT_ACCESS_H
#define STORAGE_COMPONENT_ACCESS_H

#include "types.h"

struct StorageComponentAccess
{
	StorageComponentAccess(): nodeId(0), type(0) {}

	StorageComponentAccess(Id nodeId_, int type_): nodeId(nodeId_), type(type_) {}

	bool operator<(const StorageComponentAccess& other) const
	{
		return nodeId < other.nodeId;
	}

	Id nodeId;
	int type;
};

#endif	  // STORAGE_COMPONENT_ACCESS_H
