#pragma once

#include "types.h"

struct StorageSourceLocationData {
  StorageSourceLocationData()
      : fileNodeId(0), startLine(-1), startCol(-1), endLine(-1), endCol(-1), type(0) {}

  StorageSourceLocationData(
      Id fileNodeId_, size_t startLine_, size_t startCol_, size_t endLine_, size_t endCol_, int type_)
      : fileNodeId(fileNodeId_)
      , startLine(startLine_)
      , startCol(startCol_)
      , endLine(endLine_)
      , endCol(endCol_)
      , type(type_) {}

  bool operator<(const StorageSourceLocationData& other) const {
    if(fileNodeId != other.fileNodeId) {
      return fileNodeId < other.fileNodeId;
    } else if(startLine != other.startLine) {
      return startLine < other.startLine;
    } else if(startCol != other.startCol) {
      return startCol < other.startCol;
    } else if(endLine != other.endLine) {
      return endLine < other.endLine;
    } else if(endCol != other.endCol) {
      return endCol < other.endCol;
    } else {
      return type < other.type;
    }
  }

  Id fileNodeId;
  size_t startLine;
  size_t startCol;
  size_t endLine;
  size_t endCol;
  int type;
};

struct StorageSourceLocation : public StorageSourceLocationData {
  StorageSourceLocation(): StorageSourceLocationData(), id(0) {}

  StorageSourceLocation(Id id_, const StorageSourceLocationData& data_)
      : StorageSourceLocationData(data_), id(id_) {}

  StorageSourceLocation(Id id_,
                        Id fileNodeId_,
                        size_t startLine_,
                        size_t startCol_,
                        size_t endLine_,
                        size_t endCol_,
                        int type_)
      : StorageSourceLocationData(fileNodeId_, startLine_, startCol_, endLine_, endCol_, type_)
      , id(id_) {}

  Id id;
};