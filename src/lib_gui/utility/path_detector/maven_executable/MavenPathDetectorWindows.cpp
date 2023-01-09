#include "MavenPathDetectorWindows.h"

#include "FilePath.h"
#include "utilityApp.h"

MavenPathDetectorWindows::MavenPathDetectorWindows(): PathDetector("Maven for Windows") {}

std::vector<utility::file::FilePath> MavenPathDetectorWindows::doGetPaths() const
{
	std::vector<utility::file::FilePath> paths;

	bool ok;
	utility::file::FilePath mavenPath(utility::searchPath(L"mvn.cmd", ok));
	if (ok && !mavenPath.empty() && mavenPath.exists())
	{
		paths.push_back(mavenPath);
	}
	return paths;
}
