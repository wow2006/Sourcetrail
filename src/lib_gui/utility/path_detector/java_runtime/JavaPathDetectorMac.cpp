#include "JavaPathDetectorMac.h"

#include "FilePath.h"
#include "utilityApp.h"
#include "utilityString.h"

JavaPathDetectorMac::JavaPathDetectorMac(const std::string javaVersion)
	: JavaPathDetector("Java " + javaVersion + " for Mac", javaVersion)
{
}

std::vector<utility::file::FilePath> JavaPathDetectorMac::doGetPaths() const
{
	std::vector<utility::file::FilePath> paths;
	utility::file::FilePath javaPath;

	const utility::ProcessOutput out = utility::executeProcess(L"/usr/libexec/java_home", {});

	const std::wstring output = out.exitCode == 0 ? utility::trim(out.output) : L"";
	if (!output.empty())
	{
		javaPath = utility::file::FilePath(output + L"/../MacOS/libjli.dylib").makeCanonical();
	}

	if (!javaPath.exists() && !output.empty())
	{
		javaPath = utility::file::FilePath(output + L"/lib/libjli.dylib");
	}

	if (!javaPath.exists() && !output.empty())
	{
		javaPath = utility::file::FilePath(output + L"/jre/lib/jli/libjli.dylib");
	}

	if (!javaPath.exists())
	{
		javaPath = utility::file::FilePath(L"/usr/lib/libjli.dylib");
	}

	if (!javaPath.exists() && !output.empty())
	{
		javaPath = utility::file::FilePath(output + L"/jre/lib/server/libjvm.dylib");
	}

	if (!javaPath.exists())
	{
		javaPath = utility::file::FilePath(L"/usr/lib/libjvm.dylib");
	}

	if (javaPath.exists())
	{
		paths.push_back(javaPath);
	}

	return paths;
}
