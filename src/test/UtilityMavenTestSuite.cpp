#include "catch.hpp"

#include "language_packages.h"

#if BUILD_JAVA_LANGUAGE_PACKAGE

#	include "utility::file::FilePath.h"
#	include "utility.h"
#	include "utilityMaven.h"
#	include "utilityPathDetection.h"

TEST_CASE("maven path detector is working")
{
	std::shared_ptr<PathDetector> mavenPathDetector = utility::getMavenExecutablePathDetector();
	REQUIRE(mavenPathDetector->isWorking());
}

TEST_CASE("maven wrapper detects source directories of simple projects")
{
	std::shared_ptr<PathDetector> mavenPathDetector = utility::getMavenExecutablePathDetector();
	REQUIRE(!mavenPathDetector->getPaths().empty());

	if (!mavenPathDetector->getPaths().empty())
	{
		std::vector<utility::file::FilePath> result = utility::mavenGetAllDirectoriesFromEffectivePom(
			mavenPathDetector->getPaths().front(),
			utility::file::FilePath(),
			utility::file::FilePath(L"data/UtilityMavenTestSuite/simple_maven_project"),
			utility::file::FilePath(L"data/UtilityMavenTestSuite").makeAbsolute(),
			false);

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/simple_maven_project/src/main/java").makeAbsolute()));

		REQUIRE(!utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/simple_maven_project/src/test/java").makeAbsolute()));
	}
}

TEST_CASE("maven wrapper detects source and test directories of simple projects")
{
	std::shared_ptr<PathDetector> mavenPathDetector = utility::getMavenExecutablePathDetector();
	REQUIRE(!mavenPathDetector->getPaths().empty());

	if (!mavenPathDetector->getPaths().empty())
	{
		std::vector<utility::file::FilePath> result = utility::mavenGetAllDirectoriesFromEffectivePom(
			mavenPathDetector->getPaths().front(),
			utility::file::FilePath(),
			utility::file::FilePath(L"data/UtilityMavenTestSuite/simple_maven_project"),
			utility::file::FilePath(L"data/UtilityMavenTestSuite").makeAbsolute(),
			true);

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/simple_maven_project/src/main/java").makeAbsolute()));

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/simple_maven_project/src/test/java").makeAbsolute()));
	}
}

TEST_CASE("maven wrapper detects source directories of nested modules")
{
	std::shared_ptr<PathDetector> mavenPathDetector = utility::getMavenExecutablePathDetector();
	REQUIRE(!mavenPathDetector->getPaths().empty());

	if (!mavenPathDetector->getPaths().empty())
	{
		std::vector<utility::file::FilePath> result = utility::mavenGetAllDirectoriesFromEffectivePom(
			mavenPathDetector->getPaths().front(),
			utility::file::FilePath(),
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project"),
			utility::file::FilePath(L"data/UtilityMavenTestSuite").makeAbsolute(),
			false);

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project/module_1/src/main/java")
				.makeAbsolute()));

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project/module_2/src/main/java")
				.makeAbsolute()));

		REQUIRE(!utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project/module_1/src/test/java")
				.makeAbsolute()));

		REQUIRE(!utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project/module_2/src/test/java")
				.makeAbsolute()));
	}
}

TEST_CASE("maven wrapper detects source and test directories of nested modules")
{
	std::shared_ptr<PathDetector> mavenPathDetector = utility::getMavenExecutablePathDetector();
	REQUIRE(!mavenPathDetector->getPaths().empty());

	if (!mavenPathDetector->getPaths().empty())
	{
		std::vector<utility::file::FilePath> result = utility::mavenGetAllDirectoriesFromEffectivePom(
			mavenPathDetector->getPaths().front(),
			utility::file::FilePath(),
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project"),
			utility::file::FilePath(L"data/UtilityMavenTestSuite").makeAbsolute(),
			true);

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project/module_1/src/main/java")
				.makeAbsolute()));

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project/module_2/src/main/java")
				.makeAbsolute()));

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project/module_1/src/test/java")
				.makeAbsolute()));

		REQUIRE(utility::containsElement<utility::file::FilePath>(
			result,
			utility::file::FilePath(L"data/UtilityMavenTestSuite/nested_maven_project/module_2/src/test/java")
				.makeAbsolute()));
	}
}

#endif	  // BUILD_JAVA_LANGUAGE_PACKAGE
