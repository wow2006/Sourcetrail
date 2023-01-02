// catch
#include "catch.hpp"
// internal
#include "utility.h"

TEST_CASE("digits", "[utility]") {
  REQUIRE(utility::digits(0)    == 1);
  REQUIRE(utility::digits(10)   == 2);
  REQUIRE(utility::digits(100)  == 3);
  REQUIRE(utility::digits(1000) == 4);
}
