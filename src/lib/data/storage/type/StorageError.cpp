#include "StorageError.h"

namespace utility {

StorageErrorData::StorageErrorData() = default;

StorageErrorData::StorageErrorData(std::wstring message_,
                                   std::wstring translationUnit_,
                                   bool fatal_,
                                   bool indexed_)
    : message(std::move(message_))
    , translationUnit(std::move(translationUnit_))
    , fatal(fatal_)
    , indexed(indexed_) {}

bool StorageErrorData::operator<(const StorageErrorData& other) const {
  if(message != other.message) {
    return message < other.message;
  }
  if(translationUnit != other.translationUnit) {
    return translationUnit < other.translationUnit;
  }
  if(fatal != other.fatal) {
    return fatal < other.fatal;
  }
  return indexed < other.indexed;
}

StorageError::StorageError() = default;

StorageError::StorageError(Id id_, const StorageErrorData& data): StorageErrorData(data), id(id_) {}

StorageError::StorageError(
    Id id_, std::wstring message_, std::wstring translationUnit_, bool fatal_, bool indexed_)
    : StorageErrorData(std::move(message_), std::move(translationUnit_), fatal_, indexed_)
    , id(id_) {}

}    // namespace utility