#include "CxxFrameworkPathDetector.h"

#include "FilePath.h"
#include "utilityCxxHeaderDetection.h"
#include "utilityString.h"

CxxFrameworkPathDetector::CxxFrameworkPathDetector(const std::string& compilerName)
	: PathDetector(compilerName), m_compilerName(compilerName)
{
}

std::vector<utility::file::FilePath> CxxFrameworkPathDetector::doGetPaths() const
{
	std::vector<std::wstring> paths = utility::getCxxHeaderPaths(m_compilerName);
	std::vector<utility::file::FilePath> frameworkPaths;
	for (const std::wstring& path: paths)
	{
		if (utility::isPostfix<std::wstring>(L" (framework directory)", path))
		{
			utility::file::FilePath p =
				utility::file::FilePath(utility::replace(path, L" (framework directory)", L"")).makeCanonical();
			if (p.exists())
			{
				frameworkPaths.push_back(p);
			}
		}
	}
	return frameworkPaths;
}
