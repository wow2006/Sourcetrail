// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "catch.hpp"
#include "ScopedFunctor.hpp"

TEST_CASE("ScopedFunctor", "[utility]") {
  bool called = false;
  {
    auto caller = [&called]() {
      called = true;
    };
    ScopedFunctor func(caller);
  }
  REQUIRE(called);
}
