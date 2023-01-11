// Catch2
#include "catch.hpp"
// Internal
#include "FilePath.h"
#include "utilityFile.h"
#include "ScopedFunctor.h"
#include "helper/TestFileUtilities.h"


namespace fs = std::filesystem;
using namespace utility::file;    // NOLINT(google-build-using-namespace)
using FilePaths = std::vector<FilePath>;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("partitionFilePathsBySize", "[utility,file]") {
  SECTION("empty list") {
    constexpr int PartitionCount = 2;
    const FilePaths files;
    const auto output = partitionFilePathsBySize(files, PartitionCount);
    REQUIRE(output.empty());
  }

  SECTION("non exists files") {
    const FilePaths files {"1.cpp"_f, "2.cpp"_f, "3.cpp"_f, "4.cpp"_f, "5.cpp"_f};

    SECTION("goodcase") {
      constexpr uint32_t PartitionCount = 2;
      const auto output = partitionFilePathsBySize(files, PartitionCount);
      REQUIRE_THAT(output, Catch::Matchers::Contains(files));
    }

    SECTION("non exists files and partition count is 0") {
      constexpr uint32_t PartitionCount = 0;
      const auto output = partitionFilePathsBySize(files, PartitionCount);
      REQUIRE_THAT(output, Catch::Matchers::Contains(files));
    }
  }

  SECTION("exists files") {
    const FilePaths files {createFileWithSize("1.cpp", 10),
                           createFileWithSize("2.cpp", 20),
                           createFileWithSize("3.cpp", 30),
                           createFileWithSize("4.cpp", 40),
                           createFileWithSize("5.cpp", 50)};

    ScopedFunctor cleanFiles([&files]() {
      std::error_code errorCode;
      for(const auto& file: files) {
        fs::remove(file.str(), errorCode);
      }
    });

    SECTION("partition count is 0") {
      constexpr uint32_t PartitionCount = 0;

      const auto output = partitionFilePathsBySize(files, PartitionCount);
      REQUIRE_THAT(output, Catch::Matchers::Contains(files));
    }

    SECTION("exists files and partition count is 2") {
      constexpr uint32_t PartitionCount = 2;

      const auto output = partitionFilePathsBySize(files, PartitionCount);
      REQUIRE_THAT(output, Catch::Matchers::Contains(files));
    }

    SECTION("partition count is 2 inverse") {
      constexpr uint32_t PartitionCount = 2;

      FilePaths reverseFiles = files;
      std::reverse(std::begin(reverseFiles), std::end(reverseFiles));

      const auto output = partitionFilePathsBySize(reverseFiles, PartitionCount);
      REQUIRE_THAT(output, Catch::Matchers::Contains(files));
    }

    SECTION("exists files and partition count is 6") {
      const uint32_t PartitionCount = static_cast<uint32_t>(files.size()) + 1;

      const auto output = partitionFilePathsBySize(files, PartitionCount);
      REQUIRE_THAT(output, Catch::Matchers::Contains(files));
    }
  }
}