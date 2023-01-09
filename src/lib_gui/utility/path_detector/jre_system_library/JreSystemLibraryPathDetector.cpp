#include "JreSystemLibraryPathDetector.h"

#include "JavaPathDetector.h"

#include "ApplicationSettings.h"
#include "FilePath.h"
#include "FileSystem.h"

JreSystemLibraryPathDetector::JreSystemLibraryPathDetector(
	std::shared_ptr<JavaPathDetector> javaPathDetector)
	: PathDetector(javaPathDetector->getName() + " System Library")
	, m_javaPathDetector(javaPathDetector)
{
}

std::vector<utility::file::FilePath> JreSystemLibraryPathDetector::doGetPaths() const
{
	std::vector<utility::file::FilePath> paths;
	for (const utility::file::FilePath& jrePath: m_javaPathDetector->getPaths())
	{
		const utility::file::FilePath javaRoot =
			jrePath.getParentDirectory().getParentDirectory().getParentDirectory();
		for (const utility::file::FilePath& jarPath:
			 FileSystem::getFilePathsFromDirectory(javaRoot.getConcatenated(L"lib"), {L".jar"}))
		{
			paths.push_back(jarPath);
		}
		if (!paths.empty())
		{
			break;
		}
	}
	return paths;
}
