#pragma once

#include "FilePath.h"
#include "types.h"

struct CodeScrollParams {
  enum class Type { NONE, TO_REFERENCE, TO_FILE, TO_LINE, TO_VALUE };

  enum class Target { VISIBLE, CENTER, TOP };

  static CodeScrollParams toReference(const utility::file::FilePath& filePath,
                                      Id locationId,
                                      Id scopeLocationId,
                                      Target target) {
    return CodeScrollParams(
        Type::TO_REFERENCE, target, filePath, locationId, scopeLocationId, 0, 0, false);
  }

  static CodeScrollParams toFile(const utility::file::FilePath& filePath, Target target) {
    return CodeScrollParams(Type::TO_LINE, target, filePath, 0, 0, 0, 0, false);
  }

  static CodeScrollParams toLine(const utility::file::FilePath& filePath, size_t line, Target target) {
    return CodeScrollParams(Type::TO_LINE, target, filePath, 0, 0, line, 0, false);
  }

  static CodeScrollParams toValue(size_t value, bool inListMode) {
    return CodeScrollParams(Type::TO_VALUE, Target::VISIBLE, utility::file::FilePath(), 0, 0, 0, value, inListMode);
  }

  CodeScrollParams(Type type_,
                   Target target_,
                   utility::file::FilePath filePath_,
                   Id locationId_,
                   Id scopeLocationId_,
                   size_t line_,
                   size_t value_,
                   bool inListMode_)
      : type(type_)
      , target(target_)
      , filePath(filePath_)
      , locationId(locationId_)
      , scopeLocationId(scopeLocationId_)
      , line(line_)
      , value(value_)
      , inListMode(inListMode_) {}

  CodeScrollParams() = default;

  Type type = Type::NONE;
  Target target = Target::VISIBLE;

  utility::file::FilePath filePath;

  // Reference
  Id locationId = 0;
  Id scopeLocationId = 0;

  // Line
  size_t line = 0;

  // Value
  size_t value = 0;
  bool inListMode = false;
};