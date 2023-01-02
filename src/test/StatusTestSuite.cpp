// Catch2
#include "catch.hpp"
// Internal
#include "Status.h"

TEST_CASE("Status", "[utility]") {
  utility::Status statusError{L"Error", true};
  REQUIRE(statusError.message == L"Error");
  REQUIRE(statusError.type == utility::StatusType::STATUS_ERROR);
  utility::Status statusInfo{L"Info"};
  REQUIRE(statusInfo.message == L"Info");
  REQUIRE(statusInfo.type == utility::StatusType::STATUS_INFO);
}

