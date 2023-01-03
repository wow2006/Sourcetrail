#pragma once

#include "types.h"

namespace utility {

struct StorageErrorData {
  StorageErrorData();

  StorageErrorData(std::wstring message_, std::wstring translationUnit_, bool fatal_, bool indexed_);

  bool operator<(const StorageErrorData& other) const;

  std::wstring message;
  std::wstring translationUnit;
  bool fatal = false;
  bool indexed = false;
};

struct StorageError : public StorageErrorData {
  StorageError();

  StorageError(Id id_, const StorageErrorData& data);

  StorageError(Id id_, std::wstring message_, std::wstring translationUnit_, bool fatal_, bool indexed_);

  Id id = 0;
};

}    // namespace utility