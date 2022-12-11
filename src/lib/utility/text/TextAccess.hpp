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

  ~TextAccess();

  TextAccess(const TextAccess&) = delete;
  TextAccess& operator=(const TextAccess&) = delete;
  TextAccess(TextAccess&&) = delete;
  TextAccess& operator=(TextAccess&&) = delete;

  uint32_t getLineCount() const;

  bool isEmpty() const;

  FilePath getFilePath() const;

  /**
   * @param lineNumber: starts with 1
   */
  std::string getLine(uint32_t lineNumber) const;

  /**
   * @param firstLineNumber: starts with 1
   * @param lastLineNumber: starts with 1
   */
  std::vector<std::string> getLines(uint32_t firstLineNumber, uint32_t lastLineNumber);

  const std::vector<std::string>& getAllLines() const;

  std::string getText() const;

 private:
  static std::vector<std::string> readFile(const FilePath& filePath);

  static std::vector<std::string> splitStringByLines(const std::string& text);

  TextAccess();

  bool checkIndexInRange(uint32_t index) const;

  bool checkIndexIntervalInRange(uint32_t firstIndex, uint32_t lastIndex) const;

  FilePath m_filePath;
  std::vector<std::string> m_lines;
};
