#include "JavaPathDetectorLinux.h"

#include "FilePath.h"
#include "utilityApp.h"
#include "utilityString.h"

#ifdef __x86_64__
const wchar_t jvmLibPathRelativeToJavaExecutable[] = L"/../lib/amd64/server/libjvm.so";
#else
const wchar_t jvmLibPathRelativeToJavaExecutable[] = L"/../lib/i386/server/libjvm.so";
#endif


JavaPathDetectorLinux::JavaPathDetectorLinux(const std::string javaVersion)
	: JavaPathDetector("Java " + javaVersion + " for Linux", javaVersion)
{
}

std::vector<utility::file::FilePath> JavaPathDetectorLinux::doGetPaths() const
{
	std::vector<utility::file::FilePath> paths;
	utility::file::FilePath p = getJavaInPath();
	if (!p.empty())
	{
		paths.push_back(p);
	}
	p = getJavaInJavaHome();
	if (!p.empty())
	{
		paths.push_back(p);
	}

	// some default paths for java
	paths.push_back(utility::file::FilePath(L"/etc/alternatives/java"));
	paths.push_back(utility::file::FilePath(L"/usr/lib/jvm/default/bin/java"));
	paths.push_back(utility::file::FilePath(L"/usr/lib/jvm/java-openjdk/bin/java"));

	for (const utility::file::FilePath& path: paths)
	{
		if (checkVersion(path))
		{
			utility::file::FilePath absoluteJavaPath = readLink(path);
			utility::file::FilePath jvmLibrary = getFilePathRelativeToJavaExecutable(absoluteJavaPath);
			if (jvmLibrary.exists())
			{
				std::vector<utility::file::FilePath> foundPath = {jvmLibrary};
				return foundPath;
			}
		}
	}

	return std::vector<utility::file::FilePath>();
}

utility::file::FilePath JavaPathDetectorLinux::getJavaInPath() const
{
	bool ok;
	utility::file::FilePath javaPath(utility::searchPath(L"java", ok));
	if (ok && !javaPath.empty() && javaPath.exists())
	{
		return javaPath;
	}
	return utility::file::FilePath();
}

utility::file::FilePath JavaPathDetectorLinux::readLink(const utility::file::FilePath& path) const
{
	const utility::ProcessOutput out = utility::executeProcess(
		L"readlink", std::vector<std::wstring> {L"-f", path.wstr()});

	if (out.exitCode == 0 && !out.output.empty())
	{
		utility::file::FilePath javaPath(utility::trim(out.output));

		if (!javaPath.empty())
		{
			return javaPath;
		}
	}
	return utility::file::FilePath();
}

utility::file::FilePath JavaPathDetectorLinux::getFilePathRelativeToJavaExecutable(utility::file::FilePath& javaExecutablePath) const
{
	utility::file::FilePath p = javaExecutablePath.getParentDirectory().concatenate(
		jvmLibPathRelativeToJavaExecutable);
	if (p.exists())
	{
		return p.makeCanonical();
	}
	return utility::file::FilePath();
}

utility::file::FilePath JavaPathDetectorLinux::getJavaInJavaHome() const
{
	std::string command = "";
#pragma warning(push)
#pragma warning(disable : 4996)
	char* p = getenv("JAVA_HOME");
#pragma warning(pop)
	if (p == nullptr)
	{
		return utility::file::FilePath();
	}

	utility::file::FilePath javaPath(std::string(p) + "/bin/java");
	if (!javaPath.empty() && javaPath.exists())
	{
		return javaPath;
	}
	return utility::file::FilePath();
}

bool JavaPathDetectorLinux::checkVersion(const utility::file::FilePath& path) const
{
	const utility::ProcessOutput out = utility::executeProcess(path.wstr(), {L"-version"});

	return (
		(out.exitCode == 0) &&
		(out.output.find(utility::decodeFromUtf8(m_javaVersion)) != std::string::npos));
}
