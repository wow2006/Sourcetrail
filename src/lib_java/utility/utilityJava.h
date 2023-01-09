#ifndef UTILITY_JAVA_H
#define UTILITY_JAVA_H

#include <set>
#include <string>
#include <vector>

namespace utility::file {
class FilePath;
} // namespace class utility::file
class SourceGroupSettingsWithClasspath;

namespace utility
{
std::vector<std::wstring> getRequiredJarNames();
std::string prepareJavaEnvironment();
bool prepareJavaEnvironmentAndDisplayOccurringErrors();
std::set<utility::file::FilePath> fetchRootDirectories(const std::set<utility::file::FilePath>& sourceFilePaths);
std::vector<utility::file::FilePath> getClassPath(
	const std::vector<utility::file::FilePath>& classpathItems,
	bool useJreSystemLibrary,
	const std::set<utility::file::FilePath>& sourceFilePaths);
void setJavaHomeVariableIfNotExists();
}	 // namespace utility

#endif	  // UTILITY_JAVA_H
