#include <iostream>
#include <sstream>
#include <string>

#include "ApplicationSettings.h"
#include "CommandLineParser.h"
#include "RefreshInfo.h"
#include "catch.hpp"

namespace {

constexpr auto helpExpected = R"(Usage:
  Sourcetrail [command] [option...] [positional arguments]

Commands:
  config                 Change preferences relevant to project indexing.*
  index                  Index a certain project.*

  * has its own --help

Options:
  -h [ --help ]          Print this help message
  -v [ --version ]       Version of Sourcetrail
  --project-file arg     Open Sourcetrail with this project (.srctrlprj)

Positional Arguments: 
  1: project-file
)";

constexpr auto indexHelpExpected = R"(Usage:

  Sourcetrail index [option...]

Index a certain project.


Config Options:
  -h [ --help ]          Print this help message
  -i [ --incomplete ]    Also reindex incomplete files (files with errors)
  -f [ --full ]          Index full project (omit to only index new/changed 
                         files)
  -s [ --shallow ]       Build a shallow index is supported by the project
  --project-file arg     Project file to index (.srctrlprj)

Positional Arguments: 
  1: project-file
)";

constexpr auto errorTwoProjectFileString =
    R"(ERROR: option '--project-file' cannot be specified more than once


Options:
  -h [ --help ]          Print this help message
  -v [ --version ]       Version of Sourcetrail
  --project-file arg     Open Sourcetrail with this project (.srctrlprj)

)";

}  // namespace

TEST_CASE("command line")  // NOLINT(readability-function-cognitive-complexity)
{
  SECTION("empty commandline") {
    char* args[] = {"./sourcetrail"};  // NOLINT(hicpp-avoid-c-arrays,
                                       // modernize-avoid-c-arrays,
                                       // cppcoreguidelines-avoid-c-arrays)

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(
        1, args);  // NOLINT(hicpp-no-array-decay,
                   // cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str().empty());
    REQUIRE_FALSE(parser.runWithoutGUI());
    REQUIRE_FALSE(parser.exitApplication());
  }

  SECTION("version commandline") {
    char* args[] = {"./sourcetrail", "--version"};

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(2, args);
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str() == "Sourcetrail Version 2016.1\n");
  }

  SECTION("pass a project-file") {
    std::vector<std::string> args({"--project-file", "something.srctrlprj"});

    std::stringstream outStream;
    const auto& oldOutBuf = std::cout.rdbuf(outStream.rdbuf());
    std::stringstream errStream;
    const auto& oldErrBuf = std::cerr.rdbuf(errStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldOutBuf);
    std::cerr.rdbuf(oldErrBuf);

    REQUIRE(outStream.str().empty());
    REQUIRE(errStream.str().empty());

    REQUIRE(parser.getProjectFilePath() == "something.srctrlprj");
  }

  SECTION("pass two project-file to command-line") {
    std::vector<std::string> args(
        {"--project-file", "somewhere", "--project-file", "anothersomewhere"});

    std::stringstream outStream;
    const auto& oldOutBuf = std::cout.rdbuf(outStream.rdbuf());
    std::stringstream errStream;
    const auto& oldErrBuf = std::cerr.rdbuf(errStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldOutBuf);
    std::cerr.rdbuf(oldErrBuf);

    REQUIRE(outStream.str().empty());
    CHECK_THAT(errStream.str(), Catch::Equals(errorTwoProjectFileString));
  }

  SECTION("unregisted command-line") {
    std::vector<std::string> args({"--something"});

    std::stringstream outStream;
    const auto& oldOutBuf = std::cout.rdbuf(outStream.rdbuf());
    std::stringstream errStream;
    const auto& oldErrBuf = std::cerr.rdbuf(errStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldOutBuf);
    std::cerr.rdbuf(oldErrBuf);

    REQUIRE(outStream.str().empty());
    REQUIRE(errStream.str().empty());
  }
}
