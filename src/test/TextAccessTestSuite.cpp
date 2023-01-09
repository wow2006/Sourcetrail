// STL
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string_view>
// Catch
#include "catch.hpp"
// Internal
#include "TextAccess.h"

namespace {

std::string getTestText() {
  std::string text =
      "\"But the plans were on display . . .\"\n"
      "\"On display? I eventually had to go down to the cellar to find them.\"\n"
      "\"That's the display department.\"\n"
      "\"With a torch.\"\n"
      "\"Ah, well the lights had probably gone.\"\n"
      "\"So had the stairs.\"\n"
      "\"But look, you found the notice, didn't you?\"\n"
      "\"Yes,\" said Arthur, \"yes I did. It was on display in the bottom of a locked"
      " filing cabinet stuck in a disused lavatory with a sign on the door saying"
      " Beware of the Leopard.\"\n";

  return text;
}

}  // namespace

TEST_CASE("textAccessFile from text", "[lib]") {  // NOLINT(readability-function-cognitive-complexity)
  const auto text = getTestText();
  const auto textAccess = TextAccess::createFromString(text);
  CHECK(textAccess);

  SECTION("constructor") { REQUIRE(textAccess.get() != nullptr); }

  SECTION("lines count") {
    constexpr auto lineCount = 8;

    REQUIRE(textAccess->getLineCount() == lineCount);
  }

  SECTION("lines content") {
    const auto lines = textAccess->getLines(1, 4);

    REQUIRE(lines.size() == 4);
    REQUIRE(lines[0] == "\"But the plans were on display . . .\"\n");
    REQUIRE(lines[1] == "\"On display? I eventually had to go down to the cellar to find them.\"\n");
    REQUIRE(lines[2] == "\"That's the display department.\"\n");
    REQUIRE(lines[3] == "\"With a torch.\"\n");
  }

  SECTION("lines content error handling") {
    auto lines = textAccess->getLines(3, 2);

    REQUIRE(lines.empty());

    lines = textAccess->getLines(10, 3);

    REQUIRE(lines.empty());

    lines = textAccess->getLines(1, 10);

    REQUIRE(lines.empty());

    std::string line = textAccess->getLine(0);

    REQUIRE(line.empty());

    lines = textAccess->getLines(0, 2);

    REQUIRE(line.empty());
  }

  SECTION("single line content") {
    const auto line = textAccess->getLine(6);

    REQUIRE(line == "\"So had the stairs.\"\n");
  }

  SECTION("all lines") {
    constexpr uint32_t lineCount = 8;

    const auto lines = textAccess->getAllLines();

    REQUIRE(lines.size() == lineCount);
  }
}

TEST_CASE("textAccessFile from list of string", "[lib]") {  // NOLINT(readability-function-cognitive-complexity)
  std::vector<std::string> fileLines;
  std::stringstream iStream(getTestText());
  for(std::string line; std::getline(iStream, line, '\n');) {
    fileLines.push_back(line);
  }

  const auto textAccess = TextAccess::createFromLines(fileLines);
  CHECK(textAccess);

  SECTION("constructor") { REQUIRE(textAccess.get() != nullptr); }

  SECTION("lines count") {
    constexpr auto lineCount = 8;

    REQUIRE(textAccess->getLineCount() == lineCount);
  }

  SECTION("lines content") {
    const auto lines = textAccess->getLines(1, 4);

    REQUIRE(lines.size() == 4);
    REQUIRE(lines[0] == "\"But the plans were on display . . .\"");
    REQUIRE(lines[1] == "\"On display? I eventually had to go down to the cellar to find them.\"");
    REQUIRE(lines[2] == "\"That's the display department.\"");
    REQUIRE(lines[3] == "\"With a torch.\"");
  }

  SECTION("lines content error handling") {
    auto lines = textAccess->getLines(3, 2);

    REQUIRE(lines.empty());

    lines = textAccess->getLines(10, 3);

    REQUIRE(lines.empty());

    lines = textAccess->getLines(1, 10);

    REQUIRE(lines.empty());

    std::string line = textAccess->getLine(0);

    REQUIRE(line.empty());

    lines = textAccess->getLines(0, 2);

    REQUIRE(line.empty());
  }

  SECTION("single line content") {
    const auto line = textAccess->getLine(6);

    REQUIRE(line == "\"So had the stairs.\"");
  }

  SECTION("all lines") {
    constexpr uint32_t lineCount = 8;

    const auto lines = textAccess->getAllLines();

    REQUIRE(lines.size() == lineCount);
  }
}

TEST_CASE("textAccessFile from file", "[lib]") {  // NOLINT(readability-function-cognitive-complexity)
  const utility::file::FilePath filePath(L"data/TextAccessTestSuite/text.txt");
  CHECK(filePath.isValid());

  const auto textAccess = TextAccess::createFromFile(filePath);
  CHECK(textAccess);

  SECTION("constructor") { REQUIRE(textAccess.get() != nullptr); }

  SECTION("lines count") {
    constexpr uint32_t lineCount = 7;

    REQUIRE(textAccess->getLineCount() == lineCount);
  }

  SECTION("lines content") {
    const auto lines = textAccess->getLines(1, 4);

    REQUIRE(lines.size() == 4);
    REQUIRE(lines[0] ==
            "\"If you're a researcher on this book thing and you were on Earth, you must have been "
            "gathering material on it.\"\n");
    REQUIRE(lines[1] == "\"Well, I was able to extend the original entry a bit, yes.\"\n");
    REQUIRE(lines[2] == "\"Let me see what it says in this edition, then. I've got to see it.\"\n");
    REQUIRE(lines[3] ==
            "... \"What? Harmless! Is that all it's got to say? Harmless! One word! ... Well, for "
            "God's sake I hope you managed to rectify that a bit.\"\n");
  }

  SECTION("get filePath") { REQUIRE(textAccess->getFilePath() == filePath); }
}

TEST_CASE("textAccessFile from non-exists file", "[lib]") {  // NOLINT(readability-function-cognitive-complexity)
  const utility::file::FilePath filePath(L"something/not/exists");
  const auto textAccess = TextAccess::createFromFile(filePath);
  REQUIRE_FALSE(textAccess);
}

TEST_CASE("empty textAccessFile", "[lib]") {  // NOLINT(readability-function-cognitive-complexity)
  const auto textAccess = TextAccess::createFromString({});
  CHECK(textAccess);

  SECTION("lines count") {
    constexpr uint32_t lineCount = 0;

    REQUIRE(textAccess->getLineCount() == lineCount);
  }

  SECTION("empty") {
    REQUIRE(textAccess->isEmpty());
  }

  SECTION("lines content") {
    const auto lines = textAccess->getLines(1, 4);

    REQUIRE(lines.empty());
  }

  SECTION("get text") {
    const auto lines = textAccess->getText();
    REQUIRE(lines.empty());
  }

  SECTION("get filePath") { REQUIRE(textAccess->getFilePath().empty()); }
}

