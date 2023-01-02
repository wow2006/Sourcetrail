// STL
#include <iostream>
// catch
#include "catch.hpp"
// Internal
#include "UnorderedCache.h"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("UnorderedCache", "[utility]") {
  SECTION("empty") {
    const auto EmptyString = std::string{};
    utility::UnorderedCache<std::string, uint32_t> cache([&](const std::string& string) -> uint32_t {
      return static_cast<uint32_t>(std::hash<std::string>{}(string));
    });
    const auto expectedValue = static_cast<uint32_t>(std::hash<std::string>{}(EmptyString));
    REQUIRE(cache.getValue(EmptyString) == expectedValue);
  }

  SECTION("goodcase") {
    const auto InputString = std::string{"Hello"};
    utility::UnorderedCache<std::string, uint32_t> cache([&](const std::string& string) -> uint32_t {
      return static_cast<uint32_t>(std::hash<std::string>{}(string));
    });
    const auto expectedValue = static_cast<uint32_t>(std::hash<std::string>{}(InputString));
    REQUIRE(cache.getValue(InputString) == expectedValue);
  }
}
