// STL
#include <string>
// Catch
#include "catch.hpp"
// Internal
#include "TimeStamp.h"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("secondsToString", "[utility]") {
  SECTION("good case a zero") {
    constexpr auto Output = 0;
    constexpr auto OutputString = "00:00:00:000";
    CHECK_THAT(TimeStamp::secondsToString(Output), Catch::Equals(OutputString));
  }

  SECTION("good case a second") {
    constexpr auto Output = 1;
    constexpr auto OutputString = "00:00:01:000";
    CHECK_THAT(TimeStamp::secondsToString(Output), Catch::Equals(OutputString));
  }

  SECTION("good case a minute") {
    constexpr auto Output = 60;
    constexpr auto OutputString = "00:01:00";
    CHECK_THAT(TimeStamp::secondsToString(Output), Catch::Equals(OutputString));
  }

  SECTION("good case a hour") {
    constexpr auto Output = 60 * 60;
    constexpr auto OutputString = "01:00:00";
    CHECK_THAT(TimeStamp::secondsToString(Output), Catch::Equals(OutputString));
  }

  SECTION("good case a day") {
    constexpr auto Output = 60 * 60 * 24;
    constexpr auto OutputString = "24:00:00";
    CHECK_THAT(TimeStamp::secondsToString(Output), Catch::Equals(OutputString));
  }

  SECTION("good case a day except a sec") {
    constexpr auto Output = (60 * 60 * 24) - 1;
    constexpr auto OutputString = "23:59:59";
    CHECK_THAT(TimeStamp::secondsToString(Output), Catch::Equals(OutputString));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("durationSeconds", "[utility]") {
  SECTION("good case a zero") {
    constexpr auto Output = 0;
    const auto timeStamp = TimeStamp::now();
    CHECK_THAT(TimeStamp::durationSeconds(timeStamp), Catch::WithinAbs(Output, 0));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("toString", "[utility]") {
  SECTION("goodcase") {
    constexpr auto TimeString = "2021-01-01 00:00:00.000";
    constexpr auto Output = "2021-01-01 00:00:00";
    const auto timeStamp = TimeStamp(TimeString);
    CHECK_THAT(timeStamp.toString(), Catch::Equals(Output));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("getDDMMYYYYString", "[utility]") {
  SECTION("goodcase") {
    constexpr auto TimeString = "2021-01-01 00:00:00.000";
    constexpr auto Output = "01-01-2021";
    const auto timeStamp = TimeStamp(TimeString);
    CHECK_THAT(timeStamp.getDDMMYYYYString(), Catch::Equals(Output));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("dayOfWeek", "[utility]") {
  SECTION("goodcase") {
    const std::vector<std::pair<std::string, std::string>> TimeStrings = {
      {"2021-01-01 00:00:00.000", "Friday"},
      {"2021-01-02 00:00:00.000", "Saturday"},
      {"2021-01-03 00:00:00.000", "Sunday"},
      {"2021-01-04 00:00:00.000", "Monday"},
      {"2021-01-05 00:00:00.000", "Tuesday"},
      {"2021-01-06 00:00:00.000", "Wednesday"},
      {"2021-01-07 00:00:00.000", "Thursday"},
    };

    for(const auto& [TimeString, Output] : TimeStrings) {
      const auto timeStamp = TimeStamp(TimeString);
      CHECK_THAT(timeStamp.dayOfWeek(), Catch::Equals(Output));
      CHECK_THAT(timeStamp.dayOfWeekShort(), Catch::Equals(Output.substr(0, 3)));
    }
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("delta", "[utility]") {
  SECTION("goodcase MS") {
    constexpr auto TimeString1 = "2021-01-01 00:00:00.000";
    constexpr auto TimeString2 = "2021-01-01 00:00:00.001";
    const auto Output = 1;
    const auto timeStamp1 = TimeStamp(TimeString1);
    const auto timeStamp2 = TimeStamp(TimeString2);

    CHECK(timeStamp1.deltaMS(timeStamp2) == Output);
  }

  SECTION("goodcase S") {
    constexpr auto TimeString1 = "2021-01-01 00:00:00.000";
    constexpr auto TimeString2 = "2021-01-01 00:00:01.000";
    const auto Output = 1;
    const auto timeStamp1 = TimeStamp(TimeString1);
    const auto timeStamp2 = TimeStamp(TimeString2);

    CHECK(timeStamp1.deltaS(timeStamp2) == Output);
  }

  SECTION("goodcase H") {
    constexpr auto TimeString1 = "2021-01-01 00:00:00.000";
    constexpr auto TimeString2 = "2021-01-01 01:00:00.000";
    const auto Output = 1;
    const auto timeStamp1 = TimeStamp(TimeString1);
    const auto timeStamp2 = TimeStamp(TimeString2);

    CHECK(timeStamp1.deltaHours(timeStamp2) == Output);
  }

  SECTION("goodcase D") {
    constexpr auto TimeString1 = "2021-01-01 00:00:00.000";
    constexpr auto TimeString2 = "2021-01-02 00:00:00.000";
    const auto Output = 1;
    const auto timeStamp1 = TimeStamp(TimeString1);
    const auto timeStamp2 = TimeStamp(TimeString2);

    CHECK(timeStamp1.deltaDays(timeStamp2) == Output);
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("isSameDay", "[utility]") {
  SECTION("same") {
    constexpr auto TimeString1 = "2021-01-01 00:00:00.000";
    constexpr auto TimeString2 = "2021-01-01 00:00:00.000";
    const auto timeStamp1 = TimeStamp(TimeString1);
    REQUIRE(timeStamp1.isValid());
    const auto timeStamp2 = TimeStamp(TimeString2);
    REQUIRE(timeStamp2.isValid());

    CHECK(timeStamp1.isSameDay(timeStamp2));
  }

  SECTION("not") {
    constexpr auto TimeString1 = "2021-01-01 00:00:00.000";
    constexpr auto TimeString2 = "2021-01-02 00:00:00.000";
    const auto timeStamp1 = TimeStamp(TimeString1);
    REQUIRE(timeStamp1.isValid());
    const auto timeStamp2 = TimeStamp(TimeString2);
    REQUIRE(timeStamp2.isValid());

    CHECK_FALSE(timeStamp1.isSameDay(timeStamp2));
  }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("compare", "[utility]") {
  SECTION("same") {
    constexpr auto TimeString1 = "2021-01-01 00:00:00.000";
    constexpr auto TimeString2 = "2021-01-01 00:00:00.000";
    const auto timeStamp1 = TimeStamp(TimeString1);
    REQUIRE(timeStamp1.isValid());
    const auto timeStamp2 = TimeStamp(TimeString2);
    REQUIRE(timeStamp2.isValid());

    CHECK(timeStamp1 == timeStamp2);
    CHECK_FALSE(timeStamp1 != timeStamp2);

    CHECK_FALSE(timeStamp1 < timeStamp2);
    CHECK(timeStamp1 <= timeStamp2);

    CHECK_FALSE(timeStamp2 > timeStamp1);
    CHECK(timeStamp2 >= timeStamp1);
  }

  SECTION("not equal") {
    constexpr auto TimeString1 = "2021-01-01 00:00:00.000";
    constexpr auto TimeString2 = "2021-01-02 00:00:00.000";
    const auto timeStamp1 = TimeStamp(TimeString1);
    REQUIRE(timeStamp1.isValid());
    const auto timeStamp2 = TimeStamp(TimeString2);
    REQUIRE(timeStamp2.isValid());

    CHECK_FALSE(timeStamp1 == timeStamp2);
    CHECK(timeStamp1 != timeStamp2);

    CHECK(timeStamp1 < timeStamp2);
    CHECK(timeStamp1 <= timeStamp2);

    CHECK(timeStamp2 > timeStamp1);
    CHECK(timeStamp2 >= timeStamp1);
  }
}
