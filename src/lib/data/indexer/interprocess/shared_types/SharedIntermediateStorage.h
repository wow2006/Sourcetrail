#pragma once

#include "SharedMemory.h"
#include "SharedStorageTypes.h"

class SharedIntermediateStorage {
public:
  SharedIntermediateStorage(SharedMemory::Allocator* allocator);
  ~SharedIntermediateStorage();

  std::vector<StorageNode> getStorageNodes() const;
  void setStorageNodes(const std::vector<StorageNode>& storageNodes);

  std::vector<StorageFile> getStorageFiles() const;
  void setStorageFiles(const std::vector<StorageFile>& storageFiles);

  std::vector<StorageSymbol> getStorageSymbols() const;
  void setStorageSymbols(const std::vector<StorageSymbol>& storageSymbols);

  std::vector<StorageEdge> getStorageEdges() const;
  void setStorageEdges(const std::vector<StorageEdge>& storageEdges);

  std::set<StorageLocalSymbol> getStorageLocalSymbols() const;
  void setStorageLocalSymbols(const std::set<StorageLocalSymbol>& storageLocalSymbols);

  std::set<StorageSourceLocation> getStorageSourceLocations() const;
  void setStorageSourceLocations(const std::set<StorageSourceLocation>& storageSourceLocations);

  std::set<StorageOccurrence> getStorageOccurrences() const;
  void setStorageOccurrences(const std::set<StorageOccurrence>& storageOccurrences);

  std::set<StorageComponentAccess> getStorageComponentAccesses() const;
  void setStorageComponentAccesses(const std::set<StorageComponentAccess>& storageComponentAccesses);

  std::vector<utility::StorageError> getStorageErrors() const;
  void setStorageErrors(const std::vector<utility::StorageError>& errors);

  Id getNextId() const;
  void setNextId(const Id nextId);

private:
  SharedMemory::Vector<SharedStorageFile> m_storageFiles;
  SharedMemory::Vector<SharedStorageSymbol> m_storageSymbols;
  SharedMemory::Vector<SharedStorageOccurrence> m_storageOccurrences;
  SharedMemory::Vector<SharedStorageComponentAccess> m_storageComponentAccesses;
  SharedMemory::Vector<SharedStorageNode> m_storageNodes;
  SharedMemory::Vector<SharedStorageEdge> m_storageEdges;
  SharedMemory::Vector<SharedStorageLocalSymbol> m_storageLocalSymbols;
  SharedMemory::Vector<SharedStorageSourceLocation> m_storageSourceLocations;
  SharedMemory::Vector<SharedStorageError> m_storageErrors;

  SharedMemory::Allocator* m_allocator;

  int m_nextId;
};