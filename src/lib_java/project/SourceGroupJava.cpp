#include "SourceGroupJava.h"

#include "FileManager.h"
#include "IndexerCommandJava.h"
#include "RefreshInfo.h"
#include "SourceGroupSettings.h"
#include "SourceGroupSettingsWithExcludeFilters.h"
#include "SourceGroupSettingsWithJavaStandard.h"
#include "SourceGroupSettingsWithSourceExtensions.h"
#include "logging.h"

std::set<utility::file::FilePath> SourceGroupJava::filterToContainedFilePaths(const std::set<utility::file::FilePath>& filePaths) const
{
	std::set<utility::file::FilePath> containedFilePaths;
	const std::set<utility::file::FilePath> allSourceFilePaths = getAllSourceFilePaths();
	for (const utility::file::FilePath& filePath: filePaths)
	{
		if (allSourceFilePaths.find(filePath) != allSourceFilePaths.end())
		{
			containedFilePaths.insert(filePath);
		}
	}
	return containedFilePaths;
}

std::set<utility::file::FilePath> SourceGroupJava::getAllSourceFilePaths() const
{
	FileManager fileManager;
	fileManager.update(
		getAllSourcePaths(),
		dynamic_cast<const SourceGroupSettingsWithExcludeFilters*>(getSourceGroupSettings().get())
			->getExcludeFiltersExpandedAndAbsolute(),
		dynamic_cast<const SourceGroupSettingsWithSourceExtensions*>(getSourceGroupSettings().get())
			->getSourceExtensions());
	return fileManager.getAllSourceFilePaths();
}

std::vector<std::shared_ptr<IndexerCommand>> SourceGroupJava::getIndexerCommands(
	const RefreshInfo& info) const
{
	const std::wstring languageStandard = dynamic_cast<const SourceGroupSettingsWithJavaStandard*>(
											  getSourceGroupSettings().get())
											  ->getJavaStandard();

	std::vector<utility::file::FilePath> classPath = getClassPath();

	std::vector<std::shared_ptr<IndexerCommand>> indexerCommands;
	for (const utility::file::FilePath& sourcePath: getAllSourceFilePaths())
	{
		if (info.filesToIndex.find(sourcePath) != info.filesToIndex.end())
		{
			indexerCommands.push_back(
				std::make_shared<IndexerCommandJava>(sourcePath, languageStandard, classPath));
		}
	}

	return indexerCommands;
}

std::vector<utility::file::FilePath> SourceGroupJava::getClassPath() const
{
	LOG_INFO("Retrieving classpath for indexer commands");
	std::vector<utility::file::FilePath> classPath = doGetClassPath();
	LOG_INFO("Found " + std::to_string(classPath.size()) + " paths for classpath.");
	return classPath;
}
