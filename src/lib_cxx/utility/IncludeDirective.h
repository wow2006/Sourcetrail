#pragma once

#include "FilePath.hpp"

class IncludeDirective {
 public:
  IncludeDirective(const FilePath& includedFilePath, const FilePath& includingFilePath, unsigned int lineNumber,
                   bool usesBrackets);

  FilePath getIncludedFile() const;
  FilePath getIncludingFile() const;
  std::wstring getDirective() const;
  unsigned int getLineNumber() const;

 private:
  const FilePath m_includedFilePath;
  const FilePath m_includingFilePath;
  const unsigned int m_lineNumber;
  bool m_usesBrackets;
};
