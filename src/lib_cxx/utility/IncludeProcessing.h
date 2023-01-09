#ifndef INCLUDE_PROCESSING_H
#define INCLUDE_PROCESSING_H

#include <memory>
#include <set>
#include <unordered_set>
#include <vector>

#include "OrderedCache.h"

namespace utility::file {
class FilePath;
} // namespace class utility::file
class IncludeDirective;
class TextAccess;

class IncludeProcessing
{
public:
	static std::vector<IncludeDirective> getUnresolvedIncludeDirectives(
		const std::set<utility::file::FilePath>& sourceFilePaths,
		const std::set<utility::file::FilePath>& indexedPaths,
		const std::set<utility::file::FilePath>& headerSearchDirectories,
		size_t quantileCount,
		std::function<void(float)> progress);

	static std::set<utility::file::FilePath> getHeaderSearchDirectories(
		const std::set<utility::file::FilePath>& sourceFilePaths,
		const std::set<utility::file::FilePath>& searchedPaths,
		const std::set<utility::file::FilePath>& currentHeaderSearchDirectories,
		const size_t desiredQuantileCount,
		std::function<void(float)> progress);

	static std::vector<IncludeDirective> getIncludeDirectives(const utility::file::FilePath& filePath);

	static std::vector<IncludeDirective> getIncludeDirectives(std::shared_ptr<TextAccess> textAccess);

private:
	static std::vector<IncludeDirective> doGetUnresolvedIncludeDirectives(
		std::set<utility::file::FilePath> filePathsToProcess,
		std::unordered_set<std::wstring>& processedFilePaths,
		const std::set<utility::file::FilePath>& indexedPaths,
		const std::set<utility::file::FilePath>& headerSearchDirectories);

	static utility::file::FilePath resolveIncludeDirective(
		const IncludeDirective& includeDirective, const std::set<utility::file::FilePath>& headerSearchDirectories);

	IncludeProcessing() = delete;
};

#endif	  // INCLUDE_PROCESSING_H
