#pragma once

#include "SharedMemory.h"
#include "types.h"

class BaseInterprocessDataManager {
public:
  BaseInterprocessDataManager(const std::string& sharedMemoryName,
                              size_t initialSharedMemorySize,
                              const std::string& instanceUuid,
                              Id processId,
                              bool isOwner);

  virtual ~BaseInterprocessDataManager();

  Id getProcessId() const;

protected:
  SharedMemory m_sharedMemory;

  const std::string m_instanceUuid;
  const Id m_processId;
};