// catch
#include "ScopedFunctor.h"
#include "catch.hpp"
// internal
#include "FilePath.h"
#include "FileSystem.h"
#include "helper/TestFileUtilities.h"
#include "utility.h"

namespace {

[[maybe_unused]] bool isInFiles(const std::set<utility::file::FilePath>& files,
                                const utility::file::FilePath& filename) {
  return std::end(files) != files.find(filename);
}

bool isInFileInfos(const std::vector<utility::file::FileInfo>& infos, const std::wstring& filename) {
  return ranges::cpp20::any_of(infos, [filename](const auto& info) {
    return info.path.getAbsolute().wstr() == utility::file::FilePath(filename).getCanonical().wstr();
  });
}

[[maybe_unused]] bool isInFileInfos(const std::vector<utility::file::FileInfo>& infos,
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
using namespace utility::file;    // NOLINT(google-build-using-namespace)
using FilePaths = std::vector<FilePath>;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("remove File", "[utility,file]") {
  SECTION("empty") {
    REQUIRE_FALSE(FileSystem::remove({}));
  }

  SECTION("input not exists") {
    const fs::path file = "1.cpp";

    REQUIRE_FALSE(FileSystem::remove(FilePath{file}));
  }

  SECTION("goodcase") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";

    createFileWithSize(srcFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() {
      fs::remove(srcFile, errorCode);
    });

    REQUIRE(FileSystem::remove(FilePath{srcFile}));

    REQUIRE_FALSE(fs::exists(srcFile, errorCode));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("rename File", "[utility,file]") {
  SECTION("empty") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";

    createFileWithSize(srcFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() { fs::remove(srcFile, errorCode); });

    REQUIRE_FALSE(FileSystem::rename({}, "2.cpp"_f));
    REQUIRE_FALSE(FileSystem::rename("1.cpp"_f, {}));
  }

  SECTION("input not exists") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";
    const fs::path destFile = "2.cpp";

    REQUIRE_FALSE(FileSystem::rename(FilePath {srcFile}, FilePath {destFile}));

    REQUIRE_FALSE(fs::exists(srcFile, errorCode));
    REQUIRE_FALSE(fs::exists(destFile, errorCode));
  }

  SECTION("output exists") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";
    const fs::path destFile = "2.cpp";

    createFileWithSize(srcFile, 1);
    createFileWithSize(destFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() {
      fs::remove(srcFile, errorCode);
      fs::remove(destFile, errorCode);
    });

    REQUIRE_FALSE(FileSystem::rename(FilePath {srcFile}, FilePath {destFile}));
  }

  SECTION("invalid output dir") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";
    const fs::path destFile = "/2.cpp";

    createFileWithSize(srcFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() {
      fs::remove(srcFile, errorCode);
      fs::remove(destFile, errorCode);
    });

    REQUIRE_FALSE(FileSystem::rename(FilePath {srcFile}, FilePath {destFile}));
    REQUIRE_FALSE(fs::exists(destFile, errorCode));
  }

  SECTION("goodcase") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";
    const fs::path destFile = "2.cpp";

    createFileWithSize(srcFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() {
      fs::remove(srcFile, errorCode);
      fs::remove(destFile, errorCode);
    });

    REQUIRE(FileSystem::rename(FilePath {srcFile}, FilePath {destFile}));

    REQUIRE_FALSE(fs::exists(srcFile, errorCode));
    REQUIRE(fs::exists(destFile, errorCode));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("copy File", "[utility,file]") {
  SECTION("empty") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";

    createFileWithSize(srcFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() { fs::remove(srcFile, errorCode); });

    REQUIRE_FALSE(FileSystem::copyFile({}, "2.cpp"_f));
    REQUIRE_FALSE(FileSystem::copyFile("1.cpp"_f, {}));
  }

  SECTION("input not exists") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";
    const fs::path destFile = "2.cpp";

    REQUIRE_FALSE(FileSystem::copyFile(FilePath {srcFile}, FilePath {destFile}));

    REQUIRE_FALSE(fs::exists(srcFile, errorCode));
    REQUIRE_FALSE(fs::exists(destFile, errorCode));
  }

  SECTION("output exists") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";
    const fs::path destFile = "2.cpp";

    createFileWithSize(srcFile, 1);
    createFileWithSize(destFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() {
      fs::remove(srcFile, errorCode);
      fs::remove(destFile, errorCode);
    });

    REQUIRE_FALSE(FileSystem::copyFile(FilePath {srcFile}, FilePath {destFile}));
  }

  SECTION("invalid output dir") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";
    const fs::path destFile = "/2.cpp";

    createFileWithSize(srcFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() {
      fs::remove(srcFile, errorCode);
      fs::remove(destFile, errorCode);
    });

    REQUIRE_FALSE(FileSystem::copyFile(FilePath {srcFile}, FilePath {destFile}));
    REQUIRE_FALSE(fs::exists(destFile, errorCode));
  }

  SECTION("goodcase") {
    std::error_code errorCode;
    const fs::path srcFile = "1.cpp";
    const fs::path destFile = "2.cpp";

    createFileWithSize(srcFile, 1);
    ScopedFunctor cleanDirectoryAtExit([&]() {
      fs::remove(srcFile, errorCode);
      fs::remove(destFile, errorCode);
    });

    REQUIRE(FileSystem::copyFile(FilePath {srcFile}, FilePath {destFile}));

    REQUIRE(fs::exists(srcFile, errorCode));
    REQUIRE(fs::exists(destFile, errorCode));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("create Directory", "[utility,file]") {
  SECTION("empty") {
    REQUIRE_FALSE(FileSystem::createDirectory({}));
  }

  SECTION("invalid") {
    REQUIRE_FALSE(FileSystem::createDirectory("/not/exists/"_f));
  }

  SECTION("exists") {
    fs::path directory = "test_dir";
    std::error_code errorCode;
    fs::create_directory(directory, errorCode);

    ScopedFunctor cleanDirectoryAtExit([&]() { fs::remove_all(directory, errorCode); });

    REQUIRE_FALSE(FileSystem::createDirectory(FilePath {directory}));
  }

  SECTION("goocase") {
    fs::path directory = "test_dir";
    ScopedFunctor cleanDirectoryAtExit([&]() {
      std::error_code errorCode;
      fs::remove_all(directory, errorCode);
    });
    FileSystem::createDirectory(FilePath {directory});
    REQUIRE(fs::exists(directory));
    REQUIRE(fs::is_directory(directory));
  }
}

// NOLINTNEXTLINE(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
class SubDirectoriesFixture {
public:
  SubDirectoriesFixture() {
    std::error_code errorCode;
    for(const auto& dir : mTreePaths) {
      fs::create_directories(dir.str(), errorCode);
    }
    createFileWithSize("root/a.cpp", 1);
  }

  ~SubDirectoriesFixture() {
    std::error_code errorCode;
    fs::remove_all(mRootPath.str(), errorCode);
  }

  FilePath mRootPath = "root"_f;    // NOLINT(misc-non-private-member-variables-in-classes)
  // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
  FilePaths mTreePaths {
      "root/dir_0"_f,
      "root/dir_1/temp_0/a/"_f,
      "root/dir_2/temp_1/"_f,
      "root/dir_3"_f,
  };
};

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE_METHOD(SubDirectoriesFixture, "get DirectSub Directories", "[utility,file]") {
  SECTION("empty") {
    const auto output = FileSystem::getDirectSubDirectories({});
    REQUIRE(output.empty());
  }

  SECTION("pass file") {
    const auto output = FileSystem::getDirectSubDirectories("root/a.cpp"_f);
    REQUIRE(output.empty());
  }

  SECTION("not exists") {
    const auto output = FileSystem::getDirectSubDirectories("not-exists"_f);
    REQUIRE(output.empty());
  }

  SECTION("one directory") {
    const auto output = FileSystem::getDirectSubDirectories("root/dir_1/temp_0/"_f);
    REQUIRE(output.size() == 1);
  }

  SECTION("goodcase") {
    const auto output = FileSystem::getDirectSubDirectories("root"_f);
    REQUIRE(output.size() == 4);
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE_METHOD(SubDirectoriesFixture, "get Recursive SubDirectories", "[utility,file]") {
  SECTION("empty") {
    const auto output = FileSystem::getRecursiveSubDirectories({});
    REQUIRE(output.empty());
  }

  SECTION("pass file") {
    const auto output = FileSystem::getRecursiveSubDirectories("root/a.cpp"_f);
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
