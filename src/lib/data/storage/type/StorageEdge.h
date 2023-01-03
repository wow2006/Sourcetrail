#ifndef STORAGE_EDGE_H
#define STORAGE_EDGE_H

#include "types.h"

struct StorageEdgeData
{
	StorageEdgeData(): type(0), sourceNodeId(0), targetNodeId(0) {}

	StorageEdgeData(int type_, Id sourceNodeId_, Id targetNodeId_)
		: type(type_), sourceNodeId(sourceNodeId_), targetNodeId(targetNodeId_)
	{
	}

	bool operator<(const StorageEdgeData& other) const
	{
		if (type != other.type)
		{
			return type < other.type;
		}
		else if (sourceNodeId != other.sourceNodeId)
		{
			return sourceNodeId < other.sourceNodeId;
		}
		else
		{
			return targetNodeId < other.targetNodeId;
		}
	}

	int type;
	Id sourceNodeId;
	Id targetNodeId;
};

struct StorageEdge: public StorageEdgeData
{
	StorageEdge(): StorageEdgeData(), id(0) {}

	StorageEdge(Id id_, const StorageEdgeData& data_): StorageEdgeData(data_), id(id_) {}

	StorageEdge(Id id_, int type_, Id sourceNodeId_, Id targetNodeId_)
		: StorageEdgeData(type_, sourceNodeId_, targetNodeId_), id(id_)
	{
	}

	Id id;
};

#endif	  // STORAGE_EDGE_H
