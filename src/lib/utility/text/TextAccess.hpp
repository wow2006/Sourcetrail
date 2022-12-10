#pragma once

#include <memory>
#include <string>
#include <vector>

#include "FilePath.hpp"

class TextAccess final {
 public:
  static std::shared_ptr<TextAccess> createFromFile(const FilePath& filePath);
  static std::shared_ptr<TextAccess> createFromString(const std::string& text, const FilePath& filePath = FilePath());
  static std::shared_ptr<TextAccess> createFromLines(const std::vector<std::string>& lines,
                                                     const FilePath& filePath = FilePath());

  virtual ~TextAccess() = default;

  unsigned int getLineCount() const;
  bool isEmpty() const;

  FilePath getFilePath() const;

  /**
   * @param lineNumber: starts with 1
   */
  std::string getLine(const unsigned int lineNumber) const;
  /**
   * @param firstLineNumber: starts with 1
   * @param lastLineNumber: starts with 1
   */
  std::vector<std::string> getLines(const unsigned int firstLineNumber, const unsigned int lastLineNumber);
  const std::vector<std::string>& getAllLines() const;
  std::string getText() const;

 private:
  static std::vector<std::string> readFile(const FilePath& filePath);
  static std::vector<std::string> splitStringByLines(const std::string& text);

  TextAccess();
  TextAccess(const TextAccess&);
  TextAccess operator=(const TextAccess&);

  bool checkIndexInRange(unsigned int index) const;
  bool checkIndexIntervalInRange(const unsigned int firstIndex, const unsigned int lastIndex) const;

  FilePath m_filePath;
  std::vector<std::string> m_lines;
};
