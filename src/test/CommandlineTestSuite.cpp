#include "catch.hpp"

#include "ApplicationSettings.h"
#include "CommandLineParser.h"

#include <iostream>
#include <sstream>
#include <string>

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

constexpr auto errorTwoProjectFileString = R"(ERROR: option '--project-file' cannot be specified more than once


Options:
  -h [ --help ]          Print this help message
  -v [ --version ]       Version of Sourcetrail
  --project-file arg     Open Sourcetrail with this project (.srctrlprj)

)";

}

TEST_CASE("command line") // NOLINT(readability-function-cognitive-complexity)
{
  auto appSettingsPath = ApplicationSettings::getInstance()->getFilePath();
  ApplicationSettings::getInstance()->load(FilePath(L"data/CommandlineTestSuite/settings.xml"));

  SECTION("empty commandline")
  {
    char* args[] = {"./sourcetrail"}; // NOLINT(hicpp-avoid-c-arrays, modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(1, args); // NOLINT(hicpp-no-array-decay, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str().empty());
  }

  SECTION("commandline version")
  {
    std::vector<std::string> args({"--version"});

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str() == "Sourcetrail Version 2016.1\n");
  }

  SECTION("command config help") {
    std::vector<std::string> args({"--help"});

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str() == helpExpected);
  }

  SECTION("command config filepathVector")
  {
    std::vector<std::string> args(
      {"config", "-g", "/usr", "-g", "/usr/share/include", "-g", "/opt/test/include"});

    commandline::CommandLineParser parser("2");
    parser.preparse(args);
    parser.parse();

    std::vector<FilePath> paths = ApplicationSettings::getInstance()->getHeaderSearchPaths();
    REQUIRE(paths[0].wstr() == L"/usr");
    REQUIRE(paths[1].wstr() == L"/usr/share/include");
    REQUIRE(paths[2].wstr() == L"/opt/test/include");
  }

  SECTION("command config string filepath option")
  {
    std::vector<std::string> args({"config", "--maven-path", "/opt/testpath/mvn"});

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldBuf);

    FilePath path = ApplicationSettings::getInstance()->getMavenPath();
    REQUIRE(path.wstr() == L"/opt/testpath/mvn");
  }

  SECTION("command config filepathVector comma separated")
  {
    std::vector<std::string> args(
      {"config", "--global-header-search-paths", "/usr,/usr/include,/include,/opt/include"});

    commandline::CommandLineParser parser("2");
    parser.preparse(args);
    parser.parse();

    std::vector<FilePath> paths = ApplicationSettings::getInstance()->getHeaderSearchPaths();
    REQUIRE(paths[0].wstr() == L"/usr");
    REQUIRE(paths[1].wstr() == L"/usr/include");
    REQUIRE(paths[2].wstr() == L"/include");
    REQUIRE(paths[3].wstr() == L"/opt/include");
  }

  SECTION("command config bool options")
  {
    std::vector<std::string> args({"config", "--use-processes", "false"});

    commandline::CommandLineParser parser("2");
    parser.preparse(args);
    parser.parse();

    bool processes = ApplicationSettings::getInstance()->getMultiProcessIndexingEnabled();
    REQUIRE(processes == false);

    std::vector<std::string> args1({"config", "--use-processes", "true"});

    parser.preparse(args1);
    parser.parse();

    processes = ApplicationSettings::getInstance()->getMultiProcessIndexingEnabled();
    REQUIRE(processes == true);
  }

  SECTION("pass two project-file to command-line")
  {
    std::vector<std::string> args({"--project-file", "somewhere", "--project-file", "anothersomewhere"});

    std::stringstream outStream;
    const auto& oldOutBuf = std::cout.rdbuf(outStream.rdbuf());
    std::stringstream errStream;
    const auto& oldErrBuf = std::cerr.rdbuf(errStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldOutBuf);
    std::cout.rdbuf(oldErrBuf);

    REQUIRE(outStream.str().empty());
    REQUIRE(errStream.str() == errorTwoProjectFileString);
  }

  SECTION("unregisted command-line")
  {
    std::vector<std::string> args({"--something"});

    std::stringstream outStream;
    const auto& oldOutBuf = std::cout.rdbuf(outStream.rdbuf());
    std::stringstream errStream;
    const auto& oldErrBuf = std::cerr.rdbuf(errStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldOutBuf);
    std::cout.rdbuf(oldErrBuf);

    REQUIRE(outStream.str().empty());
    REQUIRE(errStream.str().empty());
  }

  ApplicationSettings::getInstance()->load(appSettingsPath);
}
