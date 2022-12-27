#include "catch.hpp"

#include "FileManager.h"
#include "FilePath.h"
#include "FilePathFilter.h"
#include "FileSystem.h"
#include "utility.h"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("file manager has added file paths after first fetch", "[utility]") {
  std::vector<FilePath> sourcePaths;
  sourcePaths.emplace_back(FilePath(L"./data/FileManagerTestSuite/src/"));
  sourcePaths.emplace_back(FilePath(L"./data/FileManagerTestSuite/include/"));
  std::vector<FilePath> headerPaths;
  std::vector<FilePathFilter> excludeFilters;

  // catch exceptions thrown on linux build machine
  try {
    std::vector<FilePath> filePaths = FileSystem::getFilePathsFromDirectory(
        FilePath(L"./data/FileManagerTestSuite/src/"));
    REQUIRE(filePaths.size() == 3);

    std::vector<std::wstring> sourceExtensions;
    sourceExtensions.reserve(filePaths.size());
    for (const auto& path : filePaths) {
      sourceExtensions.push_back(path.extension());
    }
    REQUIRE(sourceExtensions.size() == 3);

    FileManager fileManager;
    fileManager.update(sourcePaths, excludeFilters, sourceExtensions);
    std::vector<FilePath> foundSourcePaths = utility::toVector(fileManager.getAllSourceFilePaths());

    REQUIRE(foundSourcePaths.size() == 3);
    REQUIRE(utility::containsElement<FilePath>(foundSourcePaths, filePaths[0]));
    REQUIRE(utility::containsElement<FilePath>(foundSourcePaths, filePaths[1]));
    REQUIRE(utility::containsElement<FilePath>(foundSourcePaths, filePaths[2]));
  } catch (...) {
    REQUIRE(false);
  }
}
