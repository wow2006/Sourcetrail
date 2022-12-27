// STL
#include <iostream>
// Catch2
#include "catch.hpp"
// Internal
#include "Version.h"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("version from string", "[utility]") {
  SECTION("empty") {
    const auto version = Version::fromString({});
    CHECK_FALSE(version.isValid());
    CHECK(version.isEmpty());
  }

  SECTION("invalid") {
    const auto version = Version::fromString("somthing.wrong");
    CHECK_FALSE(version.isValid());
    CHECK(version.isEmpty());
  }

  SECTION("invalid year") {
    const auto version = Version::fromString("21.1.93-2863686b");
    CHECK_FALSE(version.isValid());
    CHECK(version.isEmpty());
  }

  SECTION("invalid 2016 year") {
    const auto version = Version::fromString("2016.1.93-2863686b");
    CHECK_FALSE(version.isValid());
  }

  SECTION("invalid version") {
    const auto version = Version::fromString("2021.yak.93-2863686b");
    CHECK_FALSE(version.isValid());
    CHECK(version.isEmpty());
  }

  SECTION("negative version") {
    const auto version = Version::fromString("2021.-1.93-2863686b");
    CHECK_FALSE(version.isValid());
    CHECK(version.isEmpty());
  }

  SECTION("invalid commit") {
    const auto version = Version::fromString("2021.1.-1-2863");
    CHECK_FALSE(version.isValid());
    CHECK(version.isEmpty());
  }

  SECTION("zero number commit") {
    const auto version = Version::fromString("2021.1.91-00000000");
    CHECK(version.isValid());
    CHECK_FALSE(version.isEmpty());
  }

  SECTION("good case") {
    constexpr auto VersionString = "2021.1.93-2863686b";
    const auto version = Version::fromString(VersionString);
    CHECK(version.isValid());
    constexpr auto OutputVersionString = "2021.1-93-2863686b";
    CHECK_THAT(version.toString(), Catch::Equals(OutputVersionString));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("to string", "[utility]") {
  constexpr auto VersionString = "2021.1.93-2863686b";
  const auto version = Version::fromString(VersionString);
  REQUIRE(version.isValid());

  SECTION("toString") {
    constexpr auto OutputVersionString = "2021.1-93-2863686b";
    CHECK_THAT(version.toString(), Catch::Equals(OutputVersionString));
  }

  SECTION("toShortString") {
    constexpr auto OutputVersionString = "2021.1";
    CHECK_THAT(version.toShortString(), Catch::Equals(OutputVersionString));
  }

  SECTION("toDisplayString") {
    constexpr auto OutputVersionString = "2021.1.93";
    CHECK_THAT(version.toDisplayString(), Catch::Equals(OutputVersionString));
  }

  SECTION("toDisplayWString") {
    constexpr auto OutputVersionString = L"2021.1.93";
    CHECK(version.toDisplayWString() == OutputVersionString);
  }
}

TEST_CASE("to short version", "[utility]") {
  constexpr auto VersionString = "2021.1.93-2863686b";
  const auto version = Version::fromString(VersionString);
  REQUIRE(version.isValid());

  SECTION("toShortVersion") {
    constexpr auto OutputVersionString = "2021.1";
    CHECK_THAT(version.toShortVersion().toShortString(), Catch::Equals(OutputVersionString));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("compare minor", "[utility]") {
  constexpr auto Year = 2021;
  constexpr auto Minor = 1;
  const auto version1 = Version(Year, Minor);
  const auto version2 = Version(Year, Minor + 1);
  REQUIRE(version1.isValid());
  REQUIRE(version2.isValid());

  SECTION("less than") {
    CHECK(version1 < version2);
  }

  SECTION("greater than") {
    CHECK(version2 > version1);
  }

  SECTION("equal") {
    CHECK(version1 == version1);
    CHECK_FALSE(version1 == version2);
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("compare year", "[utility]") {
  constexpr auto Year = 2021;
  constexpr auto Minor = 1;
  const auto version1 = Version(Year, Minor);
  const auto version2 = Version(Year + 1, Minor);
  REQUIRE(version1.isValid());
  REQUIRE(version2.isValid());

  SECTION("less than") {
    CHECK(version1 < version2);
  }

  SECTION("greater than") {
    CHECK(version2 > version1);
  }

  SECTION("equal") {
    CHECK(version1 == version1);
    CHECK_FALSE(version1 == version2);
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("compare commit", "[utility]") {
  constexpr auto Year = 2021;
  constexpr auto Minor = 1;
  constexpr auto Commit = 91;
  const auto version1 = Version(Year, Minor, Commit);
  const auto version2 = Version(Year, Minor, Commit + 1);
  REQUIRE(version1.isValid());
  REQUIRE(version2.isValid());

  SECTION("less than") {
    CHECK(version1 < version2);
  }

  SECTION("greater than") {
    CHECK(version2 > version1);
  }

  SECTION("equal") {
    CHECK(version1 == version1);
    CHECK_FALSE(version1 == version2);
  }
}

TEST_CASE("increase minor version", "[utility]") {
  constexpr auto Year = 2021;
  constexpr auto Minor = 1;
  auto version = Version(Year, Minor);
  REQUIRE(version.isValid());

  SECTION("equal") {
    version += 1;
    constexpr auto OutputVersionString = "2021.2";
    CHECK_THAT(version.toShortString(), Catch::Equals(OutputVersionString));
  }
}
