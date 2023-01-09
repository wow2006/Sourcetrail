#pragma once
// STL
#include <memory>
#include <numeric>
#include <string>
#include <vector>
// Internal
#include "FilePath.h"

class TextAccess final {
public:
  /**
  * @brief Create TextAccess from file path
  *
  * @param filePath
  *
  * @return
  */
  static std::shared_ptr<TextAccess> createFromFile(const utility::file::FilePath& filePath);

  static std::shared_ptr<TextAccess> createFromString(const std::string& text,
                                                      const utility::file::FilePath& filePath = utility::file::FilePath());

  static std::shared_ptr<TextAccess> createFromLines(const std::vector<std::string>& lines,
                                                     const utility::file::FilePath& filePath = utility::file::FilePath());

  TextAccess(const TextAccess&) = delete;

  TextAccess(TextAccess&&) noexcept;

  TextAccess& operator=(const TextAccess&) = delete;

  TextAccess& operator=(TextAccess&&) noexcept;

  ~TextAccess() noexcept;

  /**
   * @brief Get the count of lines in the file
   *
   * @return Count of lines
   */
  uint32_t getLineCount() const {
    return static_cast<uint32_t>(m_lines.size());
  }

  /**
   * @brief Check if the file is empty
   *
   * @return true if the file is empty
   */
  bool isEmpty() const {
    return m_lines.empty();
  }

  /**
   * @brief Get the file name
   *
   * @return File path
   */
  utility::file::FilePath getFilePath() const {
    return m_filePath;
  }

  /**
   * @brief Access the file's text with index
   *
   * @note index starting from 1
   *
   * @param lineNumber line index of the file
   *
   * @return Text in line number, invalid lineNumber return empty string
   */
  std::string getLine(uint32_t lineNumber) const {
    if (!checkIndexInRange(lineNumber)) {
      return {};
    }

    return m_lines[lineNumber - 1];    // -1 to correct for use as index
  }

  /**
   * @brief Access the file's text with index range
   *
   * @note index starting from 1
   *
   * @param firstLineNumber First index
   * @param lastLineNumber Last index excluded
   *
   * @return Range of lines
   */
  std::vector<std::string> getLines(uint32_t firstLineNumber, uint32_t lastLineNumber);

  /**
   * @brief Get the text in file as list of strings
   *
   * @return A list of strings for the file
   */
  const std::vector<std::string>& getAllLines() const {
    return m_lines;
  }

  /**
   * @brief Get the text in file as one string
   *
   * @return A string for the file
   */
  std::string getText() const {
    return std::accumulate(std::cbegin(m_lines), std::cend(m_lines), std::string {});
  }

private:
  static std::vector<std::string> readFile(const utility::file::FilePath& filePath);

  static std::vector<std::string> splitStringByLines(const std::string& text);

  TextAccess();

  bool checkIndexInRange(uint32_t index) const;

  bool checkIndexIntervalInRange(uint32_t firstIndex, uint32_t lastIndex) const;

  utility::file::FilePath m_filePath = {};
  std::vector<std::string> m_lines;
};
