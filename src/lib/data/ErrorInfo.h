#pragma once

#include "StorageError.h"

struct ErrorInfo {
  ErrorInfo() = default;

  ErrorInfo(Id id_,
            std::wstring message_,
            std::wstring filePath_,
            size_t lineNumber_,
            size_t columnNumber_,
            std::wstring translationUnit_,
            bool fatal_,
            bool indexed_)
      : id(id_)
      , message(std::move(message_))
      , filePath(std::move(filePath_))
      , lineNumber(lineNumber_)
      , columnNumber(columnNumber_)
      , translationUnit(std::move(translationUnit_))
      , fatal(fatal_)
      , indexed(indexed_) {}

  Id id;

  std::wstring message = {};

  std::wstring filePath = {};
  size_t lineNumber = std::numeric_limits<size_t>::max();
  size_t columnNumber = std::numeric_limits<size_t>::max();

  std::wstring translationUnit = {};
  bool fatal = false;
  bool indexed = false;
};