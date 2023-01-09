#ifndef INDEXER_COMMAND_CXX_H
#define INDEXER_COMMAND_CXX_H

#include <string>
#include <vector>

#include "IndexerCommand.h"

namespace utility::file {
class FilePath;
class FilePathFilter;
} // namespace class utility::file
namespace clang::tooling
{
class JSONCompilationDatabase;
}	 // namespace clang

class IndexerCommandCxx: public IndexerCommand
{
public:
	static std::vector<utility::file::FilePath> getSourceFilesFromCDB(const utility::file::FilePath& cdbPath);
	static std::vector<utility::file::FilePath> getSourceFilesFromCDB(
		std::shared_ptr<clang::tooling::JSONCompilationDatabase> cdb, const utility::file::FilePath& cdbPath);

	static std::wstring getCompilerFlagLanguageStandard(const std::wstring& languageStandard);
	static std::vector<std::wstring> getCompilerFlagsForSystemHeaderSearchPaths(
		const std::vector<utility::file::FilePath>& systemHeaderSearchPaths);
	static std::vector<std::wstring> getCompilerFlagsForFrameworkSearchPaths(
		const std::vector<utility::file::FilePath>& frameworkSearchPaths);

	static IndexerCommandType getStaticIndexerCommandType();

	IndexerCommandCxx(
		const utility::file::FilePath& sourceFilePath,
		const std::set<utility::file::FilePath>& indexedPaths,
		const std::set<utility::file::FilePathFilter>& excludeFilters,
		const std::set<utility::file::FilePathFilter>& includeFilters,
		const utility::file::FilePath& workingDirectory,
		const std::vector<std::wstring>& compilerFlags);

	IndexerCommandType getIndexerCommandType() const override;
	size_t getByteSize(size_t stringSize) const override;

	const std::set<utility::file::FilePath>& getIndexedPaths() const;
	const std::set<utility::file::FilePathFilter>& getExcludeFilters() const;
	const std::set<utility::file::FilePathFilter>& getIncludeFilters() const;
	const std::vector<std::wstring>& getCompilerFlags() const;
	const utility::file::FilePath& getWorkingDirectory() const;

protected:
	QJsonObject doSerialize() const override;

private:
	std::set<utility::file::FilePath> m_indexedPaths;
	std::set<utility::file::FilePathFilter> m_excludeFilters;
	std::set<utility::file::FilePathFilter> m_includeFilters;
	utility::file::FilePath m_workingDirectory;
	std::vector<std::wstring> m_compilerFlags;
};

#endif	  // INDEXER_COMMAND_CXXL_H
