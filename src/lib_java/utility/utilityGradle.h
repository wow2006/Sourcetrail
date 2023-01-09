#ifndef UTILITY_GRADLE_H
#define UTILITY_GRADLE_H

#include <vector>

namespace utility::file {
class FilePath;
} // namespace class utility::file

namespace utility
{
bool gradleCopyDependencies(
	const utility::file::FilePath& projectDirectoryPath,
	const utility::file::FilePath& outputDirectoryPath,
	bool addTestDependencies);
std::vector<utility::file::FilePath> gradleGetAllSourceDirectories(
	const utility::file::FilePath& projectDirectoryPath, bool addTestDirectories);
}	 // namespace utility

#endif	  // UTILITY_GRADLE_H
