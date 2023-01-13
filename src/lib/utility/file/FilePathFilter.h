#pragma once
// Internal
#include "FilePath.h"

namespace utility::file {

/**
 * @brief
 */
class FilePathFilter final {
public:
  template <typename ContainerType>
  static bool areMatching(const ContainerType& filters, const utility::file::FilePath& filePath);

  /**
   * @brief Create a filter using a refex like pattern.
   *
   * @param filterString a regex like file path.
   */
  explicit FilePathFilter(std::wstring filterString);

  [[nodiscard]] std::wstring wstr() const;

  [[nodiscard]] bool isMatching(const utility::file::FilePath& filePath) const;

  [[nodiscard]] bool isMatching(const std::wstring& fileStr) const;

  bool operator<(const FilePathFilter& other) const;

private:
  static std::wregex convertFilterStringToRegex(const std::wstring& filterString);

  std::wstring m_filterString;
  std::wregex m_filterRegex;
};

template <typename ContainerType>
bool FilePathFilter::areMatching(const ContainerType& filters, const FilePath& filePath) {
  const auto fileStr = filePath.wstr();

  return std::any_of(std::cbegin(filters), std::cend(filters), [&fileStr](const auto& filter) {
    return filter.isMatching(fileStr);
  });
}

}    // namespace utility::file
