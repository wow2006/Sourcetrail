// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "catch.hpp"
#include "utilityString.h"

TEST_CASE("encodeToUtf8", "[utility][string]") {
  REQUIRE_THAT(utility::encodeToUtf8(L"HelloWorld!"), Catch::Equals("HelloWorld!"));
}

TEST_CASE("decodeFromUtf8", "[utility][string]") { REQUIRE(utility::decodeFromUtf8("HelloWorld!") == L"HelloWorld!"); }

TEST_CASE("split with char delimiter", "[utility][string]") {
  SECTION("empty input") {
    const auto result = utility::split("", ',');

    REQUIRE(result.size() == 1);
    REQUIRE(result.at(0).empty());
  }

  SECTION("unused delimiter") {
    const auto result = utility::split("A,B,C", '1');

    REQUIRE(result.size() == 1);
    REQUIRE(result.at(0) == "A,B,C");
  }

  SECTION("goodcase") {
    const auto result = utility::split("A,B,C", ',');

    REQUIRE(result.size() == 3);
    REQUIRE(result.at(0) == "A");
    REQUIRE(result.at(1) == "B");
    REQUIRE(result.at(2) == "C");
  }

  SECTION("end of line") {
    const auto result = utility::split("A,B,C.", '.');

    REQUIRE(result.size() == 2);
    REQUIRE(result.at(0) == "A,B,C");
    REQUIRE(result.at(1).empty());
  }
}

TEST_CASE("split with string delimiter", "[utility][string]") {
  SECTION("goodcase") {
    std::deque<std::string> result = utility::split("A->B>C", "->");

    REQUIRE(result.size() == 2);
    REQUIRE(result.at(0) == "A");
    REQUIRE(result.at(1) == "B>C");
  }

  SECTION("empty string") {
    std::deque<std::string> result = utility::split("", "->");

    REQUIRE(result.size() == 1);
    REQUIRE(result.at(0).empty());
  }

  SECTION("unused delimiter") {
    std::deque<std::string> result = utility::split("A:B:C", ";");

    REQUIRE(result.size() == 1);
    REQUIRE(result.at(0) == "A:B:C");
  }

  SECTION("ddelimiters next to each") {
    std::deque<std::string> result = utility::split("A::B:C", ':');

    REQUIRE(result.size() == 4);
    REQUIRE(result.at(0) == "A");
    REQUIRE(result.at(1).empty());
    REQUIRE(result.at(2) == "B");
    REQUIRE(result.at(3) == "C");
  }

  SECTION("delimiter at start") {
    std::deque<std::string> result = utility::split(":B:C", ':');

    REQUIRE(result.size() == 3);
    REQUIRE(result.at(0).empty());
    REQUIRE(result.at(1) == "B");
    REQUIRE(result.at(2) == "C");
  }

  SECTION("delimiter at end") {
    std::deque<std::string> result = utility::split("B:C:", ':');

    REQUIRE(result.size() == 3);
    REQUIRE(result.at(0) == "B");
    REQUIRE(result.at(1) == "C");
    REQUIRE(result.at(2).empty());
  }
}

TEST_CASE("split with string delimiter to vector", "[utility][string]") {
  SECTION("goodcase") {
    const auto result = utility::splitToVector("A->B>C", "->");

    REQUIRE(result.size() == 2);
    REQUIRE(result.at(0) == "A");
    REQUIRE(result.at(1) == "B>C");
  }

  SECTION("empty string") {
    const auto result = utility::splitToVector("", "->");

    REQUIRE(result.size() == 1);
    REQUIRE(result.at(0).empty());
  }

  SECTION("unused delimiter") {
    const auto result = utility::splitToVector("A:B:C", ";");

    REQUIRE(result.size() == 1);
    REQUIRE(result.at(0) == "A:B:C");
  }

  SECTION("ddelimiters next to each") {
    const auto result = utility::splitToVector("A::B:C", ':');

    REQUIRE(result.size() == 4);
    REQUIRE(result.at(0) == "A");
    REQUIRE(result.at(1).empty());
    REQUIRE(result.at(2) == "B");
    REQUIRE(result.at(3) == "C");
  }

  SECTION("delimiter at start") {
    const auto result = utility::splitToVector(":B:C", ':');

    REQUIRE(result.size() == 3);
    REQUIRE(result.at(0).empty());
    REQUIRE(result.at(1) == "B");
    REQUIRE(result.at(2) == "C");
  }

  SECTION("delimiter at end") {
    const auto result = utility::splitToVector("B:C:", ':');

    REQUIRE(result.size() == 3);
    REQUIRE(result.at(0) == "B");
    REQUIRE(result.at(1) == "C");
    REQUIRE(result.at(2).empty());
  }
}

TEST_CASE("join with char delimiter", "[utility][string]") {
  SECTION("goodcase") {
    std::deque<std::string> list;
    list.emplace_back("A");
    list.emplace_back("B");
    list.emplace_back("C");

    std::string result = utility::join(list, ',');
    REQUIRE(result == "A,B,C");
  }

  SECTION("empty list") {
    std::deque<std::string> list;
    std::string result = utility::join(list, ',');
    REQUIRE(result.empty());
  }

  SECTION("empty strings in list") {
    std::deque<std::string> list;
    list.emplace_back("A");
    list.emplace_back("");
    list.emplace_back("");

    std::string result = utility::join(list, ':');
    REQUIRE(result == "A::");
  }
}

TEST_CASE("join with string delimiter", "[utility][string]") {
  SECTION("goodcase") {
    std::deque<std::string> list;
    list.emplace_back("A");
    list.emplace_back("B");
    list.emplace_back("C");

    std::string result = utility::join(list, "==");
    REQUIRE(result == "A==B==C");
  }
}

TEST_CASE("tokenize with string", "[utility][string]") {
  SECTION("goodcase") {
    std::deque<std::string> result = utility::tokenize("A->B->C", "->");

    REQUIRE(result.size() == 5);
    REQUIRE(result.at(0) == "A");
    REQUIRE(result.at(1) == "->");
    REQUIRE(result.at(2) == "B");
    REQUIRE(result.at(3) == "->");
    REQUIRE(result.at(4) == "C");
  }

  SECTION("string and delimiter at start") {
    std::deque<std::string> result = utility::tokenize("->B", "->");

    REQUIRE(result.size() == 2);
    REQUIRE(result.at(0) == "->");
    REQUIRE(result.at(1) == "B");
  }

  SECTION("string and delimiter at end") {
    std::deque<std::string> result = utility::tokenize("C+", '+');

    REQUIRE(result.size() == 2);
    REQUIRE(result.at(0) == "C");
    REQUIRE(result.at(1) == "+");
  }

  SECTION("deque") {
    std::deque<std::string> result = utility::tokenize("A->B=C->D", "->");
    result = utility::tokenize(result, "=");

    REQUIRE(result.size() == 7);
    REQUIRE(result.at(0) == "A");
    REQUIRE(result.at(1) == "->");
    REQUIRE(result.at(2) == "B");
    REQUIRE(result.at(3) == "=");
    REQUIRE(result.at(4) == "C");
    REQUIRE(result.at(5) == "->");
    REQUIRE(result.at(6) == "D");
  }
}

TEST_CASE("substr", "[utility][string]") {
  SECTION("before first with single delimiter occurrence") {
    REQUIRE(utility::substrBeforeFirst("foo bar", ' ') == "foo");
  }

  SECTION("before first with multiple delimiter occurrences") {
    REQUIRE(utility::substrBeforeFirst("foo bar foo", ' ') == "foo");
  }

  SECTION("before first with no delimiter occurrence") {
    REQUIRE(utility::substrBeforeFirst("foobar", ' ') == "foobar");
  }

  SECTION("before first with delimiter at start") { REQUIRE(utility::substrBeforeFirst(" foobar", ' ') == ""); }

  SECTION("before first with delimiter at end") { REQUIRE(utility::substrBeforeFirst("foobar ", ' ') == "foobar"); }

  SECTION("before last with single delimiter occurrence") {
    REQUIRE(utility::substrBeforeLast("foo bar", ' ') == "foo");
  }

  SECTION("before last with multiple delimiter occurrences") {
    REQUIRE(utility::substrBeforeLast("foo bar foo", ' ') == "foo bar");
  }

  SECTION("before last with no delimiter occurrence") { REQUIRE(utility::substrBeforeLast("foobar", ' ') == "foobar"); }

  SECTION("before last with delimiter at start") { REQUIRE(utility::substrBeforeLast(" foobar", ' ') == ""); }

  SECTION("before last with delimiter at end") { REQUIRE(utility::substrBeforeLast("foobar ", ' ') == "foobar"); }

  SECTION("after with single delimiter occurrence") { REQUIRE(utility::substrAfter("foo bar", ' ') == "bar"); }

  SECTION("after with multiple delimiter occurrences") {
    REQUIRE(utility::substrAfter("foo bar foo", ' ') == "bar foo");
  }

  SECTION("after with no delimiter occurrence") { REQUIRE(utility::substrAfter("foobar", ' ') == "foobar"); }

  SECTION("after with delimiter at start") { REQUIRE(utility::substrAfter(" foobar", ' ') == "foobar"); }

  SECTION("after with delimiter at end") { REQUIRE(utility::substrAfter("foobar ", ' ') == ""); }
}

TEST_CASE("isPrefix", "[utility][string]") {
  SECTION("empty string is detected as prefix of any other string") {
    const std::string foo = "foo";

    REQUIRE(utility::isPrefix<std::string>("", foo));
  }

  SECTION("prefix of bigger text is detected as prefix") {
    const std::string foobar = "foobar";
    const std::string foo = "foo";

    REQUIRE(utility::isPrefix(foo, foobar));
  }

  SECTION("prefix is detected as prefix of self") {
    const std::string foo = "foo";

    REQUIRE(utility::isPrefix(foo, foo));
  }

  SECTION("different texts are not detected of prefixes of each other") {
    const std::string foo = "foo";
    const std::string bar = "bar";

    REQUIRE(!utility::isPrefix(foo, bar));
    REQUIRE(!utility::isPrefix(bar, foo));
  }
}

TEST_CASE("to lower case", "[utility][string]") {
  REQUIRE("foobar" == utility::toLowerCase("FooBar"));
  REQUIRE("foobar" == utility::toLowerCase("FOOBAR"));
  REQUIRE("foobar" == utility::toLowerCase("foobar"));
}

TEST_CASE("equals case insensitive", "[utility][string]") {
  SECTION("different cases") {
    const std::string foo = "FooBar";
    const std::string foo2 = "foobar";

    REQUIRE(utility::equalsCaseInsensitive(foo, foo2));
  }

  SECTION("same cases") {
    const std::string foo = "foobar";
    const std::string foo2 = "foobar";

    REQUIRE(utility::equalsCaseInsensitive(foo, foo2));
  }

  SECTION("different strings") {
    const std::string foo = "foo";
    const std::string foo2 = "foobar";

    REQUIRE(!utility::equalsCaseInsensitive(foo, foo2));
  }
}

TEST_CASE("replace", "[utility][string]") {
  REQUIRE("fubar" == utility::replace("foobar", "oo", "u"));
  REQUIRE("fuuuubar" == utility::replace("foobar", "o", "uu"));
  REQUIRE("bar" == utility::replace("foobar", "foo", ""));
  REQUIRE("foobar" == utility::replace("foobar", "", "i"));
  REQUIRE("foobar" == utility::replace("foobar", "", ""));
  REQUIRE("" == utility::replace("", "foo", "bar"));
  REQUIRE("foobar" == utility::replace("foobar", "ba", "ba"));
}

TEST_CASE("caseInsensitiveLess", "[utility][string]") {
  SECTION("should return false when comparing empty wstrings") {
    REQUIRE_FALSE(utility::caseInsensitiveLess(L"", L""));
  }

  SECTION("should return false when both wstrings are equal") {
    REQUIRE_FALSE(utility::caseInsensitiveLess(L"ab_cd!", L"ab_cd!"));
  }

  SECTION(
      "should return false when both wstrings have"
      "different cases but after lower casing are equal") {
    REQUIRE_FALSE(utility::caseInsensitiveLess(L"ab_CD!", L"aB_cD!"));
  }

  SECTION("should return true when first wstring is empty and second not") {
    REQUIRE(utility::caseInsensitiveLess(L"", L"ab"));
  }

  SECTION("should return false when second wstring is empty and first not") {
    REQUIRE_FALSE(utility::caseInsensitiveLess(L"ab", L""));
  }

  SECTION("should return true when first wstring is prefix of second") {
    REQUIRE(utility::caseInsensitiveLess(L"ab_cd!", L"ab_cd!e"));
  }

  SECTION("should return false when second wstring is prefix of first") {
    REQUIRE_FALSE(utility::caseInsensitiveLess(L"ab_cd!e", L"ab_cd!"));
  }

  SECTION(
      "should return true when after lower casing first wstring, first is prefix "
      "of second") {
    REQUIRE(utility::caseInsensitiveLess(L"aB_cd!", L"ab_cd!e"));
  }

  SECTION(
      "should return true when after lower casing second wstring, first is "
      "prefix of second") {
    REQUIRE(utility::caseInsensitiveLess(L"ab_cd!", L"ab_cD!e"));
  }

  SECTION(
      "should return true when after lower casing both wstrings, first is prefix "
      "of second") {
    REQUIRE(utility::caseInsensitiveLess(L"aB_cd!", L"ab_cD!E"));
  }

  SECTION(
      "should return false when after lower casing first wstring, second is "
      "prefix of first") {
    REQUIRE_FALSE(utility::caseInsensitiveLess(L"ab_Cd!e", L"ab_cd!"));
  }

  SECTION(
      "should return false when after lower casing second wstring, second is "
      "prefix of first") {
    REQUIRE_FALSE(utility::caseInsensitiveLess(L"ab_cd!e", L"Ab_cd!"));
  }

  SECTION(
      "should return false when after lower casing both wstrings, second is "
      "prefix of first") {
    REQUIRE_FALSE(utility::caseInsensitiveLess(L"ab_cD!E", L"aB_cd!"));
  }
}