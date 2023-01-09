#include "catch.hpp"

#include "FilePathFilter.h"

TEST_CASE("file path filter finds exact match") {
  utility::file::FilePathFilter filter(L"test.h");

  REQUIRE(filter.isMatching(utility::file::FilePath(L"test.h")));
}

TEST_CASE("file path filter finds match with single asterisk in same level") {
  utility::file::FilePathFilter filter(L"*test.*");

  REQUIRE(filter.isMatching(utility::file::FilePath(L"this_is_a_test.h")));
}

TEST_CASE("file path filter finds match with single asterisk in different level") {
  utility::file::FilePathFilter filter(L"*/this_is_a_test.h");

  REQUIRE(filter.isMatching(utility::file::FilePath(L"folder/this_is_a_test.h")));
}

TEST_CASE("file path filter does not find match with single asterisk in different level") {
  utility::file::FilePathFilter filter(L"*/test.h");

  REQUIRE(!filter.isMatching(utility::file::FilePath(L"test.h")));
}

TEST_CASE("file path filter finds match with multiple asterisk in same level") {
  utility::file::FilePathFilter filter(L"**test.h");

  REQUIRE(filter.isMatching(utility::file::FilePath(L"folder/this_is_a_test.h")));
}

TEST_CASE("file path filter finds match with multiple asterisk in different level") {
  utility::file::FilePathFilter filter(L"root/**/test.h");

  REQUIRE(filter.isMatching(utility::file::FilePath(L"root/folder1/folder2/test.h")));
}

TEST_CASE("file path filter does not find match with multiple asterisk in different level") {
  utility::file::FilePathFilter filter(L"**/test.h");

  REQUIRE(!filter.isMatching(utility::file::FilePath(L"folder/this_is_a_test.h")));
}

TEST_CASE("file path filter escapes dot character") {
  utility::file::FilePathFilter filter(L"test.h");

  REQUIRE(!filter.isMatching(utility::file::FilePath(L"testyh")));
}

TEST_CASE("file path filter escapes plus character") {
  REQUIRE(utility::file::FilePathFilter(L"folder/test+.h").isMatching(utility::file::FilePath(L"folder/test+.h")));
}

TEST_CASE("file path filter escapes minus character") {
  REQUIRE(utility::file::FilePathFilter(L"folder/test[-].h").isMatching(utility::file::FilePath(L"folder/test[-].h")));
}

TEST_CASE("file path filter escapes dollar character") {
  REQUIRE(utility::file::FilePathFilter(L"folder/test$.h").isMatching(utility::file::FilePath(L"folder/test$.h")));
}

TEST_CASE("file path filter escapes circumflex character") {
  REQUIRE(utility::file::FilePathFilter(L"folder/test^.h").isMatching(utility::file::FilePath(L"folder/test^.h")));
}

TEST_CASE("file path filter escapes open round brace character") {
  REQUIRE(utility::file::FilePathFilter(L"folder/test(.h").isMatching(utility::file::FilePath(L"folder/test(.h")));
}

TEST_CASE("file path filter escapes close round brace character") {
  REQUIRE(utility::file::FilePathFilter(L"folder\\test).h").isMatching(utility::file::FilePath(L"folder/test).h")));
}

TEST_CASE("file path filter escapes open curly brace character") {
  REQUIRE(utility::file::FilePathFilter(L"folder/test{.h").isMatching(utility::file::FilePath(L"folder/test{.h")));
}

TEST_CASE("file path filter escapes close curly brace character") {
  REQUIRE(utility::file::FilePathFilter(L"folder/test}.h").isMatching(utility::file::FilePath(L"folder/test}.h")));
}

TEST_CASE("file path filter escapes open squared brace character") {
  REQUIRE(utility::file::FilePathFilter(L"folder/test[.h").isMatching(utility::file::FilePath(L"folder/test[.h")));
}

TEST_CASE("file path filter escapes close squared brace character") {
  REQUIRE(utility::file::FilePathFilter(L"folder\\test].h").isMatching(utility::file::FilePath(L"folder/test].h")));
}

TEST_CASE("file path filter finds backslash if slash was provided") {
  utility::file::FilePathFilter filter(L"folder/test.h");

  REQUIRE(filter.isMatching(utility::file::FilePath(L"folder\\test.h")));
}

TEST_CASE("file path filter finds slash if backslash was provided") {
  utility::file::FilePathFilter filter(L"folder\\test.h");

  REQUIRE(filter.isMatching(utility::file::FilePath(L"folder/test.h")));
}
