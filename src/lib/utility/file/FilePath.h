#pragma once

#include <memory>
#include <string>
#include <vector>

namespace boost::filesystem {
class path;
}    // namespace boost::filesystem

class FilePath final {
public:
  FilePath();
  explicit FilePath(const std::string& filePath);
  explicit FilePath(const std::wstring& filePath);
  FilePath(const FilePath& other);
  FilePath& operator=(const FilePath& other);
  FilePath(FilePath&& other) noexcept;
  FilePath& operator=(FilePath&& other) noexcept;
  FilePath(const std::wstring& filePath, const std::wstring& base);
  ~FilePath();

  bool operator==(const FilePath& other) const;
  bool operator!=(const FilePath& other) const;
  bool operator<(const FilePath& other) const;

  boost::filesystem::path getPath() const;

  bool empty() const;
  bool exists() const noexcept;
  bool recheckExists() const;
  bool isDirectory() const;
  bool isAbsolute() const;
  bool isValid() const;

  FilePath getParentDirectory() const;

  FilePath& makeAbsolute();
  FilePath getAbsolute() const;
  FilePath& makeCanonical();
  FilePath getCanonical() const;
  FilePath& makeRelativeTo(const FilePath& other);
  FilePath getRelativeTo(const FilePath& other) const;
  FilePath& concatenate(const FilePath& other);
  FilePath getConcatenated(const FilePath& other) const;
  FilePath& concatenate(const std::wstring& other);
  FilePath getConcatenated(const std::wstring& other) const;
  FilePath getLowerCase() const;
  std::vector<FilePath> expandEnvironmentVariables() const;

  bool contains(const FilePath& other) const;

  std::string str() const;
  std::wstring wstr() const;
  std::wstring fileName() const;

  std::wstring extension() const;
  FilePath withoutExtension() const;
  FilePath replaceExtension(const std::wstring& extension) const;
  bool hasExtension(const std::vector<std::wstring>& extensions) const;

private:
  std::unique_ptr<boost::filesystem::path> m_path;

  mutable bool m_exists;
  mutable bool m_checkedExists;
  mutable bool m_isDirectory;
  mutable bool m_checkedIsDirectory;
  mutable bool m_canonicalized;
};
