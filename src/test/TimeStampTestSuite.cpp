// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include "catch.hpp"
#include "TimeStamp.hpp"

TEST_CASE("now", "[lib]") {
  auto now = TimeStamp::now();
  REQUIRE(now.isValid());
}

TEST_CASE("secondsToString", "[lib]") { // NOLINT(readability-function-cognitive-complexity)
  REQUIRE(TimeStamp::secondsToString(-1)  == "00:00:-1"); // Need to be fixed
  REQUIRE(TimeStamp::secondsToString(0)  == "00:00:00");
  REQUIRE(TimeStamp::secondsToString(30) == "00:00:30");
  REQUIRE(TimeStamp::secondsToString(60) == "00:01:00");
  REQUIRE(TimeStamp::secondsToString(90) == "00:01:30");
  REQUIRE(TimeStamp::secondsToString(60*60) == "01:00:00");
  REQUIRE(TimeStamp::secondsToString(60*60 + 90) == "01:01:30:000"); // Need to double check
  REQUIRE(TimeStamp::secondsToString(60*60*10) == "10:00:00");
}

TEST_CASE("durationSeconds", "[lib]") {
  REQUIRE(TimeStamp::durationSeconds(TimeStamp::now())  == 0);
}

TEST_CASE("constructor", "[lib]") { // NOLINT(readability-function-cognitive-complexity)
  SECTION("deafult") {
    TimeStamp time;
    REQUIRE_FALSE(time.isValid());
  }

  SECTION("empty") {
    TimeStamp time("");
    REQUIRE_FALSE(time.isValid());
  }

  SECTION("invalid") {
    REQUIRE_THROWS_AS(TimeStamp("invalid"), boost::bad_lexical_cast);
  }

  SECTION("goodcase") {
    TimeStamp time("2002-01-20 23:59:59.000");
    REQUIRE(time.isValid());
    REQUIRE(time.toString() == "2002-01-20 23:59:59");
    REQUIRE(time.getDDMMYYYYString() == "20-01-2002");
    REQUIRE(time.dayOfWeek() == "Sunday");
    REQUIRE(time.dayOfWeekShort() == "Sun");
  }
}

TEST_CASE("dayOfWeek", "[lib]") { // NOLINT(readability-function-cognitive-complexity)
  SECTION("Sunday") {
    TimeStamp time("2002-01-20 23:59:59.000");
    REQUIRE(time.dayOfWeek() == "Sunday");
  }
  SECTION("Monday") {
    TimeStamp time("2002-01-21 23:59:59.000");
    REQUIRE(time.dayOfWeek() == "Monday");
  }
  SECTION("Tuesday") {
    TimeStamp time("2002-01-22 23:59:59.000");
    REQUIRE(time.dayOfWeek() == "Tuesday");
  }
  SECTION("Wednesday") {
    TimeStamp time("2002-01-23 23:59:59.000");
    REQUIRE(time.dayOfWeek() == "Wednesday");
  }
  SECTION("Thursday") {
    TimeStamp time("2002-01-24 23:59:59.000");
    REQUIRE(time.dayOfWeek() == "Thursday");
  }
  SECTION("Friday") {
    TimeStamp time("2002-01-25 23:59:59.000");
    REQUIRE(time.dayOfWeek() == "Friday");
  }
  SECTION("Saturday") {
    TimeStamp time("2002-01-26 23:59:59.000");
    REQUIRE(time.dayOfWeek() == "Saturday");
  }
}

TEST_CASE("delta", "[lib]") { // NOLINT(readability-function-cognitive-complexity)
  SECTION("Miliseconds") {
    TimeStamp time0("2002-01-20 23:59:59.000");
    TimeStamp time1("2002-01-21 00:00:00.000");
    REQUIRE(time0.deltaMS(time1) == 1000);
  }

  SECTION("Seconds") {
    TimeStamp time0("2002-01-20 23:59:59.000");
    TimeStamp time1("2002-01-21 00:00:00.000");
    REQUIRE(time0.deltaS(time1) == 1);
  }

  SECTION("Hours") {
    TimeStamp time0("2002-01-20 00:00:00.000");
    TimeStamp time1("2002-01-20 01:00:00.000");
    REQUIRE(time0.deltaHours(time1) == 1);
  }

  SECTION("Days") {
    TimeStamp time0("2002-01-20 23:59:59.000");
    TimeStamp time1("2002-01-21 00:00:00.000");
    REQUIRE(time0.deltaDays(time1) == 1);
  }
}

TEST_CASE("isSameDay", "[lib]") {
  SECTION("Miliseconds") {
    TimeStamp time0("2002-01-20 23:59:59.000");
    TimeStamp time1("2002-01-20 00:00:00.000");
    REQUIRE(time0.isSameDay(time1));
  }
}
