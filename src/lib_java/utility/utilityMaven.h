#ifndef UTILITY_MAVEN_H
#define UTILITY_MAVEN_H

#include <string>
#include <vector>

namespace utility::file {
class FilePath;
} // namespace class utility::file

namespace utility
{
std::wstring mavenGenerateSources(
	const utility::file::FilePath& mavenPath, const utility::file::FilePath& settingsFilePath, const utility::file::FilePath& projectDirectoryPath);
bool mavenCopyDependencies(
	const utility::file::FilePath& mavenPath,
	const utility::file::FilePath& settingsFilePath,
	const utility::file::FilePath& projectDirectoryPath,
	const utility::file::FilePath& outputDirectoryPath);
std::vector<utility::file::FilePath> mavenGetAllDirectoriesFromEffectivePom(
	const utility::file::FilePath& mavenPath,
	const utility::file::FilePath& settingsFilePath,
	const utility::file::FilePath& projectDirectoryPath,
	const utility::file::FilePath& outputDirectoryPath,
	bool addTestDirectories);
}	 // namespace utility

#endif	  // UTILITY_MAVEN_H
