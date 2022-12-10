// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "catch.hpp"
#include "TextCodec.h"

TEST_CASE("TextCodec", "[utility]") {
  TextCodec codec("UTF-8");
  REQUIRE(codec.isValid());
  REQUIRE(codec.getName() == "UTF-8");
}
