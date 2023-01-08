#pragma once

#include "types.h"

struct StorageComponentAccess {
  StorageComponentAccess(): nodeId(0), type(0) {}

  StorageComponentAccess(Id nodeId_, int type_): nodeId(nodeId_), type(type_) {}

  bool operator<(const StorageComponentAccess& other) const {
    return nodeId < other.nodeId;
  }

  Id nodeId;
  int type;
};