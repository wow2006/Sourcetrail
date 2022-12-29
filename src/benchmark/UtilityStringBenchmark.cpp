// STL
#include <iostream>
#include <string>
// Catch2
#include "catch.hpp"
// Internal
#include "utilityString.h"

TEST_CASE("split", "[utility][string]") {
  const std::string input = "HelloWorld! HelloWorld! HelloWorld!";
  BENCHMARK("short") {
    return utility::split(input,  ' ');
  };
}

