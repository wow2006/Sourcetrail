#include "CxxHeaderPathDetector.h"

#include "FilePath.h"
#include "utilityCxxHeaderDetection.h"
#include "utilityString.h"

CxxHeaderPathDetector::CxxHeaderPathDetector(const std::string& compilerName)
	: PathDetector(compilerName), m_compilerName(compilerName)
{
}

std::vector<utility::file::FilePath> CxxHeaderPathDetector::doGetPaths() const
{
	std::vector<std::wstring> paths = utility::getCxxHeaderPaths(m_compilerName);
	std::vector<utility::file::FilePath> headerSearchPaths;

	for (const std::wstring& path: paths)
	{
		if (!utility::isPostfix<std::wstring>(L" (framework directory)", path) &&
			utility::file::FilePath(path).getCanonical().exists() &&
			!utility::file::FilePath(path).getCanonical().getConcatenated(L"/stdarg.h").exists())
		{
			headerSearchPaths.push_back(utility::file::FilePath(path).makeCanonical());
		}
	}

	return headerSearchPaths;
}
