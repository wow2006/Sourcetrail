#include "StorageAccess.h"

StorageAccess::~StorageAccess() = default;

void StorageAccess::setUseErrorCache(bool /*enabled*/) {}

void StorageAccess::addErrorsToCache(const std::vector<ErrorInfo>& /*newErrors*/,
                                     const ErrorCountInfo& /*errorCount*/) {}