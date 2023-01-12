// catch
#include "catch.hpp"
// internal
#include "FilePath.h"
#include "FileSystem.h"
#include "utility.h"
#include "helper/TestFileUtilities.h"

namespace {

bool isInFiles(const std::set<utility::file::FilePath>& files,
               const utility::file::FilePath& filename) {
  return std::end(files) != files.find(filename);
}

bool isInFileInfos(const std::vector<utility::file::FileInfo>& infos, const std::wstring& filename) {
  return ranges::cpp20::any_of(infos, [filename](const auto& info) {
    return info.path.getAbsolute().wstr() == utility::file::FilePath(filename).getCanonical().wstr();
  });
}

bool isInFileInfos(const std::vector<utility::file::FileInfo>& infos,
                   const std::wstring& filename,
                   const std::wstring& filename2) {
  return ranges::cpp20::any_of(infos, [filename, filename2](const auto& info) {
    return info.path.wstr() == utility::file::FilePath(filename).getCanonical().wstr() ||
        info.path.wstr() == utility::file::FilePath(filename2).getCanonical().wstr();
  });
}

}    // namespace

TEST_CASE("find cpp files", "[utility,file]") {
  std::vector<std::wstring> cppFiles = utility::convert<utility::file::FilePath, std::wstring>(
      utility::file::FileSystem::getFilePathsFromDirectory(
          utility::file::FilePath(L"data/FileSystemTestSuite"), {L".cpp"}),
      [](const utility::file::FilePath& filePath) { return filePath.wstr(); });

  REQUIRE(cppFiles.size() == 4);
  REQUIRE(utility::containsElement<std::wstring>(cppFiles, L"data/FileSystemTestSuite/main.cpp"));
  REQUIRE(utility::containsElement<std::wstring>(
      cppFiles, L"data/FileSystemTestSuite/Settings/sample.cpp"));
  REQUIRE(
      utility::containsElement<std::wstring>(cppFiles, L"data/FileSystemTestSuite/src/main.cpp"));
  REQUIRE(
      utility::containsElement<std::wstring>(cppFiles, L"data/FileSystemTestSuite/src/test.cpp"));
}

TEST_CASE("find h files", "[utility,file]") {
  std::vector<std::wstring> headerFiles = utility::convert<utility::file::FilePath, std::wstring>(
      utility::file::FileSystem::getFilePathsFromDirectory(
          utility::file::FilePath(L"data/FileSystemTestSuite"), {L".h"}),
      [](const utility::file::FilePath& filePath) { return filePath.wstr(); });

  REQUIRE(headerFiles.size() == 3);
  REQUIRE(
      utility::containsElement<std::wstring>(headerFiles, L"data/FileSystemTestSuite/tictactoe.h"));
  REQUIRE(utility::containsElement<std::wstring>(
      headerFiles, L"data/FileSystemTestSuite/Settings/player.h"));
  REQUIRE(
      utility::containsElement<std::wstring>(headerFiles, L"data/FileSystemTestSuite/src/test.h"));
}

TEST_CASE("find all source files", "[utility,file]") {
  std::vector<std::wstring> sourceFiles = utility::convert<utility::file::FilePath, std::wstring>(
      utility::file::FileSystem::getFilePathsFromDirectory(
          utility::file::FilePath(L"data/FileSystemTestSuite"), {L".h", L".hpp", L".cpp"}),
      [](const utility::file::FilePath& filePath) { return filePath.wstr(); });

  REQUIRE(sourceFiles.size() == 8);
}

TEST_CASE("find file infos", "[utility,file]") {
#ifndef _WIN32
  std::vector<utility::file::FilePath> directoryPaths;
  directoryPaths.emplace_back(L"./data/FileSystemTestSuite/src");

  std::vector<utility::file::FileInfo> files = utility::file::FileSystem::getFileInfosFromPaths(
      directoryPaths, {L".h", L".hpp", L".cpp"}, false);

  REQUIRE(files.size() == 2);
  REQUIRE(isInFileInfos(files, L"./data/FileSystemTestSuite/src/test.cpp"));
  REQUIRE(isInFileInfos(files, L"./data/FileSystemTestSuite/src/test.h"));
#endif
}

#if 0
TEST_CASE("find file infos with symlinks", "[utility,file]") {
#  ifndef _WIN32
  std::vector<utility::file::FilePath> directoryPaths;
  directoryPaths.emplace_back(L"./data/FileSystemTestSuite/src");

  auto files = FileSystem::getFileInfosFromPaths(directoryPaths, {L".h", L".hpp", L".cpp"}, true);

  REQUIRE(files.size() == 5);
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/Settings/player.h",
                        L"./data/FileSystemTestSuite/player.h"));
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/Settings/sample.cpp",
                        L"./data/FileSystemTestSuite/sample.cpp"));
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/main.cpp",
                        L"./data/FileSystemTestSuite/src/Settings/src/main.cpp"));
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/test.cpp",
                        L"./data/FileSystemTestSuite/src/Settings/src/test.cpp"));
  REQUIRE(isInFileInfos(files,
                        L"./data/FileSystemTestSuite/src/test.h",
                        L"./data/FileSystemTestSuite/src/Settings/src/test.h"));
#  endif
}
#endif

TEST_CASE("find symlinked directories", "[utility,file]") {
#ifndef _WIN32
  std::vector<utility::file::FilePath> directoryPaths;
  directoryPaths.emplace_back("./data/FileSystemTestSuite/src");

  std::set<utility::file::FilePath> dirs = utility::file::FileSystem::getSymLinkedDirectories(
      directoryPaths);

  REQUIRE(dirs.size() == 2);
#endif
}

namespace fs = std::filesystem;
using namespace utility::file;
using FilePaths = std::vector<FilePath>;

class RecursiveSubDirectoriesFixture {
public:
  RecursiveSubDirectoriesFixture() {
    std::error_code errorCode;
    for(const auto& dir : mTreePaths) {
      fs::create_directories(dir.str(), errorCode);
    }
  }

  ~RecursiveSubDirectoriesFixture() {
    std::error_code errorCode;
    fs::remove_all(mRootPath.str(), errorCode);
  }

  FilePath mRootPath = "root"_f;
  FilePaths mTreePaths {
    "root/dir_0"_f,
    "root/dir_1/temp_0/a/"_f,
    "root/dir_2/temp_1/"_f,
    "root/dir_3"_f,
  };
};

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE_METHOD(RecursiveSubDirectoriesFixture, "get Recursive SubDirectories", "[utility,file]") {
  SECTION("empty") {
    const auto output = FileSystem::getRecursiveSubDirectories({});
    REQUIRE(output.empty());
  }

  SECTION("not exists") {
    const auto output = FileSystem::getRecursiveSubDirectories("not-exists"_f);
    REQUIRE(output.empty());
  }

  SECTION("empty directory") {
    const auto output = FileSystem::getRecursiveSubDirectories("root/dir_2/temp_1/"_f);
    REQUIRE(output.empty());
  }

  SECTION("one directory") {
    const auto output = FileSystem::getRecursiveSubDirectories("root/dir_1/temp_0/"_f);
    REQUIRE(output.size() == 1);
  }

  SECTION("goodcase") {
    const auto output = FileSystem::getRecursiveSubDirectories("root"_f);
    REQUIRE(output.size() == 7);
  }
}
