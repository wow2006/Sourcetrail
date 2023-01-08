#pragma once

#include "types.h"

enum class ParseLocationType { TOKEN, SCOPE, SIGNATURE, QUALIFIER, LOCAL };

struct ParseLocation {
  ParseLocation();
  ParseLocation(Id fileId, size_t lineNumber, size_t columnNumber);
  ParseLocation(Id fileId,
                size_t startLineNumber,
                size_t startColumnNumber,
                size_t endLineNumber,
                size_t endColumnNumber);

  bool isValid() const;

  Id fileId;
  size_t startLineNumber;
  size_t startColumnNumber;
  size_t endLineNumber;
  size_t endColumnNumber;
};
