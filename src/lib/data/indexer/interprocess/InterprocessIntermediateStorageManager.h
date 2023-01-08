#pragma once

#include "BaseInterprocessDataManager.h"

class IntermediateStorage;

class InterprocessIntermediateStorageManager : public BaseInterprocessDataManager {
public:
  InterprocessIntermediateStorageManager(const std::string& instanceUuid, Id processId, bool isOwner);
  ~InterprocessIntermediateStorageManager() override;

  void pushIntermediateStorage(const std::shared_ptr<IntermediateStorage>& intermediateStorage);
  std::shared_ptr<IntermediateStorage> popIntermediateStorage();

  size_t getIntermediateStorageCount();

private:
  static const char* s_sharedMemoryNamePrefix;
  static const char* s_intermediateStoragesKeyName;

  size_t m_insertsWithoutGrowth;
};