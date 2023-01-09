#pragma once

#include "language_packages.h"

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "FilePathFilter.h"
#include "SharedMemory.h"

class IndexerCommand;

class SharedIndexerCommand {
public:
  void fromLocal(IndexerCommand* indexerCommand);
  static std::shared_ptr<IndexerCommand> fromShared(const SharedIndexerCommand& indexerCommand);

  SharedIndexerCommand(SharedMemory::Allocator* allocator);
  ~SharedIndexerCommand();

  utility::file::FilePath getSourceFilePath() const;
  void setSourceFilePath(const utility::file::FilePath& filePath);

#if BUILD_CXX_LANGUAGE_PACKAGE

  std::set<utility::file::FilePath> getIndexedPaths() const;
  void setIndexedPaths(const std::set<utility::file::FilePath>& indexedPaths);

  std::set<FilePathFilter> getExcludeFilters() const;
  void setExcludeFilters(const std::set<FilePathFilter>& excludeFilters);

  std::set<FilePathFilter> getIncludeFilters() const;
  void setIncludeFilters(const std::set<FilePathFilter>& includeFilters);

  utility::file::FilePath getWorkingDirectory() const;
  void setWorkingDirectory(const utility::file::FilePath& workingDirectory);

  std::vector<std::wstring> getCompilerFlags() const;
  void setCompilerFlags(const std::vector<std::wstring>& compilerFlags);

#endif    // BUILD_CXX_LANGUAGE_PACKAGE
#if BUILD_JAVA_LANGUAGE_PACKAGE

  std::wstring getLanguageStandard() const;
  void setLanguageStandard(const std::wstring& languageStandard);

  std::vector<utility::file::FilePath> getClassPaths() const;
  void setClassPaths(const std::vector<utility::file::FilePath>& classPaths);

#endif    // BUILD_JAVA_LANGUAGE_PACKAGE

private:
  enum Type {
    UNKNOWN = 0,
#if BUILD_CXX_LANGUAGE_PACKAGE
    CXX,
#endif    // BUILD_CXX_LANGUAGE_PACKAGE
#if BUILD_JAVA_LANGUAGE_PACKAGE
    JAVA,
#endif    // BUILD_JAVA_LANGUAGE_PACKAGE
#if BUILD_PYTHON_LANGUAGE_PACKAGE
    PYTHON,
#endif    // BUILD_PYTHON_LANGUAGE_PACKAGE
  };

  Type getType() const;
  void setType(const Type type);

  Type m_type;

  // indexer command
  SharedMemory::String m_sourceFilePath;

#if BUILD_CXX_LANGUAGE_PACKAGE
  SharedMemory::Vector<SharedMemory::String> m_indexedPaths;
  SharedMemory::Vector<SharedMemory::String> m_excludeFilters;
  SharedMemory::Vector<SharedMemory::String> m_includeFilters;
  SharedMemory::String m_workingDirectory;
  SharedMemory::Vector<SharedMemory::String> m_compilerFlags;
#endif    // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE
  SharedMemory::String m_languageStandard;
  SharedMemory::Vector<SharedMemory::String> m_classPaths;
#endif    // BUILD_JAVA_LANGUAGE_PACKAGE
};