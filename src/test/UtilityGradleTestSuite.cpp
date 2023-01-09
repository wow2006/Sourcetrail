#include "catch.hpp"

#include "language_packages.h"

#if BUILD_JAVA_LANGUAGE_PACKAGE
#	ifdef WIN32

#		include "utility::file::FilePath.h"
#		include "FileSystem.h"
#		include "utility.h"
#		include "utilityGradle.h"

utility::file::FilePath tmpFolder = utility::file::FilePath(L"data/UtilityGradleTestSuite/tmp");

void cleanup()
{
	if (tmpFolder.recheckExists())
	{
		for (const utility::file::FilePath& path: FileSystem::getFilePathsFromDirectory(tmpFolder))
		{
			FileSystem::remove(path);
		}
		FileSystem::remove(tmpFolder);
	}
}

TEST_CASE("gradle wrapper detects source directories of simple projects")
{
	std::vector<utility::file::FilePath> result = utility::gradleGetAllSourceDirectories(
		utility::file::FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project"), false);

	REQUIRE(utility::containsElement<utility::file::FilePath>(
		result,
		utility::file::FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project/src/main/java").makeAbsolute()));

	REQUIRE(!utility::containsElement<utility::file::FilePath>(
		result,
		utility::file::FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project/src/test/java").makeAbsolute()));
}

TEST_CASE("gradle wrapper detects source and test directories of simple projects")
{
	std::vector<utility::file::FilePath> result = utility::gradleGetAllSourceDirectories(
		utility::file::FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project"), true);

	REQUIRE(utility::containsElement<utility::file::FilePath>(
		result,
		utility::file::FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project/src/main/java").makeAbsolute()));

	REQUIRE(utility::containsElement<utility::file::FilePath>(
		result,
		utility::file::FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project/src/test/java").makeAbsolute()));
}

TEST_CASE("gradle wrapper detects source dependencies of simple projects")
{
	std::vector<std::wstring> requiredDependencies = {L"joda-time-2.2.jar"};

	cleanup();
	REQUIRE(utility::gradleCopyDependencies(
		utility::file::FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project"),
		tmpFolder.makeAbsolute(),
		false));

	const std::vector<utility::file::FilePath> copiedDependencies = FileSystem::getFilePathsFromDirectory(tmpFolder);

	for (const std::wstring requiredDependency: requiredDependencies)
	{
		REQUIRE(utility::containsElement(
			copiedDependencies, tmpFolder.getConcatenated(requiredDependency)));
	}
	cleanup();
}

TEST_CASE("gradle wrapper detects source and test dependencies of simple projects")
{
	std::vector<std::wstring> requiredDependencies = {
		L"joda-time-2.2.jar", L"hamcrest-core-1.3.jar", L"junit-4.12.jar"};

	cleanup();
	REQUIRE(utility::gradleCopyDependencies(
		utility::file::FilePath(L"data/UtilityGradleTestSuite/simple_gradle_project"),
		tmpFolder.makeAbsolute(),
		true));

	const std::vector<utility::file::FilePath> copiedDependencies = FileSystem::getFilePathsFromDirectory(tmpFolder);

	for (const std::wstring requiredDependency: requiredDependencies)
	{
		REQUIRE(utility::containsElement(
			copiedDependencies, tmpFolder.getConcatenated(requiredDependency)));
	}
	cleanup();
}

#	endif	  // WIN32
#endif		  // BUILD_JAVA_LANGUAGE_PACKAGE
