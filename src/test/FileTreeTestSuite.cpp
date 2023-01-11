// catch
#include "catch.hpp"
// internal
#include "FilePath.h"
#include "utilityString.h"
#include <filesystem>
#define private public    // For testing use
#include "FileTree.h"
#undef private
#include "helper/TestFileUtilities.h"

namespace fs = std::filesystem;
using namespace utility::file;    // NOLINT(google-build-using-namespace)
using FilePaths = std::vector<FilePath>;

void print(const FilePaths& files) {
  if(files.empty()) {
    fmt::print("[]\n");
    return;
  }
  fmt::print("[\n");
  for(const auto& file : files) {
    fmt::print("\t{}\n", file.str());
  }
  fmt::print("]\n");
}

void print(const FileTree& fileTree) {
  fmt::print("rootPath: {}\n", fileTree.m_rootPath.str());
  for(const auto& [key, files] : fileTree.m_files) {
    fmt::print("{}: ", utility::encodeToUtf8(key));
    for(const auto& file : files) {
      fmt::print("{},", file.str());
    }
    fmt::print("\n");
  }
}

class UniqueTestsFixture {
public:
  UniqueTestsFixture() {
    constexpr auto StartFileSize = 10U;
    constexpr auto DeltaFileSize = 10U;
    std::error_code errorCode;
    fs::create_directories(mDirectory / "temp", errorCode);

    size_t fileSize = StartFileSize;
    for(const auto& file : mFiles) {
      createFileWithSize(file.str(), fileSize);
      fileSize += DeltaFileSize;
    }
  }

  ~UniqueTestsFixture() {
    std::error_code errorCode;
    fs::remove_all(mDirectory, errorCode);
  }

  fs::path mDirectory = "test_dir";    // NOLINT(misc-non-private-member-variables-in-classes)
  // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
  FilePaths mFiles {
      "test_dir/1.cpp"_f,
      "test_dir/2.cpp"_f,
      "test_dir/3.cpp"_f,
      "test_dir/temp/4.cpp"_f,
      "test_dir/temp/5.cpp"_f,
      "test_dir/temp/6.cpp"_f,
  };
};

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE_METHOD(UniqueTestsFixture, "FileTree", "[utility,file]") {
  SECTION("input empty") {
    const FileTree fileTree({});
    // The behave is drivern by rootPath.getAbsolute().makeCanonical()
    REQUIRE(fileTree.m_rootPath.str() == fs::canonical(fs::current_path()));
  }

  SECTION("Directory") {
    const FileTree fileTree(FilePath {mDirectory});
    REQUIRE(fileTree.m_rootPath.str() == fs::canonical(mDirectory));
    const auto expected = std::unordered_map<std::wstring, std::set<FilePath>> {
        {L"1.cpp", {"test_dir/1.cpp"_f}},
    };

    for(const auto& file : mFiles) {
      REQUIRE(fileTree.m_files.find(utility::decodeFromUtf8(file.str())) !=
              std::cbegin(fileTree.m_files));
    }
  }

  SECTION("File") {
    const FileTree fileTree(mFiles.front());
    REQUIRE(fileTree.m_files.find(utility::decodeFromUtf8(mFiles.front().str())) !=
            std::cbegin(fileTree.m_files));
  }

  SECTION("getAbsoluteRootPathForRelativeFilePath") {
    const FileTree fileTree(FilePath {mDirectory});
    REQUIRE(fileTree.getAbsoluteRootPathForRelativeFilePath("test_dir/3.cpp"_f).str() == fs::canonical("."));
    REQUIRE(fileTree.getAbsoluteRootPathForRelativeFilePath("test_dir/"_f).empty());
    REQUIRE(fileTree.getAbsoluteRootPathForRelativeFilePath(""_f).empty());
  }

  SECTION("getAbsoluteRootPathsForRelativeFilePath") {
    const FileTree fileTree(FilePath {mDirectory});
    REQUIRE(fileTree.getAbsoluteRootPathsForRelativeFilePath("test_dir/3.cpp"_f).size() == 1);
    REQUIRE(fileTree.getAbsoluteRootPathsForRelativeFilePath("test_dir/3.cpp"_f).front().str() == fs::canonical("."));
    REQUIRE(fileTree.getAbsoluteRootPathsForRelativeFilePath("test_dir/"_f).empty());
    REQUIRE(fileTree.getAbsoluteRootPathsForRelativeFilePath(""_f).empty());
  }
}
