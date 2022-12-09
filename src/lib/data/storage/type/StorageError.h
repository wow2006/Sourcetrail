#ifndef STORAGE_ERROR_H
#define STORAGE_ERROR_H

#include <string>

#include "FilePath.h"
#include "types.h"

struct StorageErrorData {
  StorageErrorData() : m_message(L""), m_translationUnit(L""), m_fatal(0), m_indexed(0) {}

  StorageErrorData(std::wstring message, std::wstring translationUnit, bool fatal, bool indexed)
      : m_message(std::move(message)),
        m_translationUnit(std::move(translationUnit)),
        m_fatal(fatal),
        m_indexed(indexed) {}

  bool operator<(const StorageErrorData& other) const {
    if (m_message != other.m_message) {
      return m_message < other.m_message;
    } else if (m_translationUnit != other.m_translationUnit) {
      return m_translationUnit < other.m_translationUnit;
    } else if (m_fatal != other.m_fatal) {
      return m_fatal < other.m_fatal;
    } else {
      return m_indexed < other.m_indexed;
    }
  }

  std::wstring m_message;
  std::wstring m_translationUnit;
  bool m_fatal;
  bool m_indexed;
};

struct StorageError : public StorageErrorData {
  StorageError() : StorageErrorData(), m_id(0) {}

  StorageError(Id id, const StorageErrorData& data) : StorageErrorData(data), m_id(id) {}

  StorageError(Id id, std::wstring message, std::wstring translationUnit, bool fatal, bool indexed)
      : StorageErrorData(std::move(message), std::move(translationUnit), fatal, indexed), m_id(id) {}

  Id m_id;
};

#endif  // STORAGE_ERROR_H
