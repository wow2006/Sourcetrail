#include "IncludeProcessing.h"

#include <iterator>
#include <set>
#include <unordered_set>

#include "ApplicationSettings.h"
#include "FilePath.h"
#include "FileTree.h"
#include "IncludeDirective.h"
#include "TextAccess.h"
#include "TextCodec.h"
#include "utility.h"
#include "utilityString.h"

namespace
{
struct IncludeDirectiveComparator
{
	bool operator()(const IncludeDirective& a, const IncludeDirective& b) const
	{
		return a.getIncludedFile() < b.getIncludedFile();
	}
};
}	 // namespace

std::vector<IncludeDirective> IncludeProcessing::getUnresolvedIncludeDirectives(
	const std::set<utility::file::FilePath>& sourceFilePaths,
	const std::set<utility::file::FilePath>& indexedPaths,
	const std::set<utility::file::FilePath>& headerSearchDirectories,
	const size_t desiredQuantileCount,
	std::function<void(float)> progress)
{
	std::unordered_set<std::wstring> processedFilePaths;
	std::set<IncludeDirective, IncludeDirectiveComparator> unresolvedIncludeDirectives;

	std::vector<std::vector<utility::file::FilePath>> parts = utility::splitToEquallySizedParts(
		utility::toVector(sourceFilePaths), desiredQuantileCount);

	for (size_t i = 0; i < parts.size(); i++)
	{
		progress(float(i) / parts.size());

		const std::vector<IncludeDirective> directives = doGetUnresolvedIncludeDirectives(
			utility::toSet(parts[i]), processedFilePaths, indexedPaths, headerSearchDirectories);
		std::copy(
			directives.begin(),
			directives.end(),
			std::inserter(unresolvedIncludeDirectives, unresolvedIncludeDirectives.end()));
	}

	std::vector<IncludeDirective> ret;

	for (const IncludeDirective& directive: unresolvedIncludeDirectives)
	{
		ret.push_back(directive);
	}

	progress(1.0f);

	return ret;
}

std::set<utility::file::FilePath> IncludeProcessing::getHeaderSearchDirectories(
	const std::set<utility::file::FilePath>& sourceFilePaths,
	const std::set<utility::file::FilePath>& searchedPaths,
	const std::set<utility::file::FilePath>& currentHeaderSearchDirectories,
	const size_t desiredQuantileCount,
	std::function<void(float)> progress)
{
	progress(0.0f);

	std::vector<std::shared_ptr<FileTree>> existingFileTrees;
	for (const utility::file::FilePath& searchedPath: searchedPaths)
	{
		existingFileTrees.push_back(std::make_shared<FileTree>(searchedPath));
	}

	std::set<utility::file::FilePath> headerSearchDirectories;
	std::unordered_set<std::wstring> processedFilePaths;
	std::vector<std::vector<utility::file::FilePath>> parts = utility::splitToEquallySizedParts(
		utility::toVector(sourceFilePaths), desiredQuantileCount);

	for (size_t i = 0; i < parts.size(); i++)
	{
		progress(float(i) / parts.size());

		std::set<utility::file::FilePath> unprocessedFilePaths(parts[i].begin(), parts[i].end());

		while (!unprocessedFilePaths.empty())
		{
			std::transform(
				unprocessedFilePaths.begin(),
				unprocessedFilePaths.end(),
				std::inserter(processedFilePaths, processedFilePaths.begin()),
				[](const utility::file::FilePath& p) { return p.getAbsolute().wstr(); });

			std::set<utility::file::FilePath> unprocessedFilePathsForNextIteration;

			for (const utility::file::FilePath& unprocessedFilePath: unprocessedFilePaths)
			{
				for (const IncludeDirective& includeDirective:
					 getIncludeDirectives(unprocessedFilePath))
				{
					const utility::file::FilePath includedFilePath = includeDirective.getIncludedFile();

					utility::file::FilePath foundIncludedPath = resolveIncludeDirective(
						includeDirective, currentHeaderSearchDirectories);
					if (foundIncludedPath.empty())
					{
						for (std::shared_ptr<FileTree> existingFileTree: existingFileTrees)
						{
							// TODO: handle the case where a file can be found by two different paths
							const utility::file::FilePath rootPath =
								existingFileTree->getAbsoluteRootPathForRelativeFilePath(
									includedFilePath);
							if (!rootPath.empty())
							{
								foundIncludedPath = rootPath.getConcatenated(includedFilePath);
								if (foundIncludedPath.exists())
								{
									headerSearchDirectories.insert(rootPath);
									break;
								}
							}
						}
					}
					if (foundIncludedPath.exists())
					{
						foundIncludedPath.makeCanonical();
						if (processedFilePaths.find(foundIncludedPath.wstr()) ==
							processedFilePaths.end())
						{
							unprocessedFilePathsForNextIteration.insert(foundIncludedPath);
						}
					}
				}
			}

			unprocessedFilePaths = unprocessedFilePathsForNextIteration;
		}
	}

	progress(1.0f);

	return headerSearchDirectories;
}

std::vector<IncludeDirective> IncludeProcessing::getIncludeDirectives(const utility::file::FilePath& filePath)
{
	if (filePath.exists())
	{
		return getIncludeDirectives(TextAccess::createFromFile(filePath));
	}
	return std::vector<IncludeDirective>();
}

std::vector<IncludeDirective> IncludeProcessing::getIncludeDirectives(
	std::shared_ptr<TextAccess> textAccess)
{
	std::vector<IncludeDirective> includeDirectives;

	TextCodec codec(ApplicationSettings::getInstance()->getTextEncoding());
	const std::vector<std::string> lines = textAccess->getAllLines();
	for (unsigned i = 0; i < lines.size(); i++)
	{
		const std::wstring line = codec.decode(lines[i]);
		const std::wstring lineTrimmedToHash = utility::trim(line);
		if (utility::isPrefix<std::wstring>(L"#", lineTrimmedToHash))
		{
			const std::wstring lineTrimmedToInclude = utility::trim(lineTrimmedToHash.substr(1));
			if (utility::isPrefix<std::wstring>(L"include", lineTrimmedToInclude))
			{
				std::wstring includeString = utility::substrBetween<std::wstring>(
					lineTrimmedToInclude, L"<", L">");
				bool usesBrackets = true;
				if (includeString.empty())
				{
					includeString = utility::substrBetween<std::wstring>(
						lineTrimmedToInclude, L"\"", L"\"");
					usesBrackets = false;
				}

				if (!includeString.empty())
				{
					// lines are 1 based
					includeDirectives.push_back(IncludeDirective(
						utility::file::FilePath(includeString), textAccess->getFilePath(), i + 1, usesBrackets));
				}
			}
		}
	}

	return includeDirectives;
}

std::vector<IncludeDirective> IncludeProcessing::doGetUnresolvedIncludeDirectives(
	std::set<utility::file::FilePath> filePathsToProcess,
	std::unordered_set<std::wstring>& processedFilePaths,
	const std::set<utility::file::FilePath>& indexedPaths,
	const std::set<utility::file::FilePath>& headerSearchDirectories)
{
	std::vector<IncludeDirective> unresolvedIncludeDirectives;

	while (!filePathsToProcess.empty())
	{
		std::transform(
			filePathsToProcess.begin(),
			filePathsToProcess.end(),
			std::inserter(processedFilePaths, processedFilePaths.begin()),
			[](const utility::file::FilePath& p) { return p.getAbsolute().makeCanonical().wstr(); });

		std::set<utility::file::FilePath> filePathsToProcessForNextIteration;

		for (const utility::file::FilePath& filePath: filePathsToProcess)
		{
			for (const IncludeDirective& includeDirective: getIncludeDirectives(filePath))
			{
				const utility::file::FilePath resolvedIncludePath =
					resolveIncludeDirective(includeDirective, headerSearchDirectories).makeCanonical();
				if (resolvedIncludePath.empty())
				{
					unresolvedIncludeDirectives.push_back(includeDirective);
				}
				else if (processedFilePaths.find(resolvedIncludePath.wstr()) == processedFilePaths.end())
				{
					for (const utility::file::FilePath& indexedPath: indexedPaths)
					{
						if (indexedPath.contains(resolvedIncludePath))
						{
							filePathsToProcessForNextIteration.insert(resolvedIncludePath);
							break;
						}
					}
				}
			}
		}
		filePathsToProcess.clear();
		filePathsToProcess.swap(filePathsToProcessForNextIteration);
	}

	return unresolvedIncludeDirectives;
}

utility::file::FilePath IncludeProcessing::resolveIncludeDirective(
	const IncludeDirective& includeDirective, const std::set<utility::file::FilePath>& headerSearchDirectories)
{
	const utility::file::FilePath includedFilePath = includeDirective.getIncludedFile();

	{
		// check for an absolute include path
		if (includedFilePath.isAbsolute())
		{
			const utility::file::FilePath resolvedIncludePath = includedFilePath;
			if (resolvedIncludePath.exists())
			{
				return includedFilePath;
			}
		}
	}

	{
		// check for an include path relative to the including path
		const utility::file::FilePath resolvedIncludePath =
			includeDirective.getIncludingFile().getParentDirectory().concatenate(includedFilePath);
		if (resolvedIncludePath.exists())
		{
			return resolvedIncludePath;
		}
	}

	{
		// check for an include path relative to the header search directories
		for (const utility::file::FilePath& headerSearchDirectory: headerSearchDirectories)
		{
			const utility::file::FilePath resolvedIncludePath = headerSearchDirectory.getConcatenated(
				includedFilePath);
			if (resolvedIncludePath.exists())
			{
				return resolvedIncludePath;
			}
		}
	}

	return utility::file::FilePath();
}
