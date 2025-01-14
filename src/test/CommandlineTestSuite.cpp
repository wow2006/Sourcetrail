#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "ApplicationSettings.h"
#include "CommandLineParser.h"
#include "CommandlineCommand.h"
#include "CommandlineCommandConfig.h"
#include "CommandlineCommandIndex.h"
#include "RefreshInfo.h"
#include "catch.hpp"
#include "trompeloeil.hpp"

namespace {

constexpr auto helpExpected = R"(Usage:
  Sourcetrail [command] [option...] [positional arguments]

Commands:

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

class MockCommand : public commandline::CommandlineCommand {
 public:
  MockCommand(const std::string& name, const std::string& description, commandline::CommandLineParser* parser)
      : CommandlineCommand(name, description, parser) {}

  ~MockCommand() override = default;

  MAKE_MOCK0(setup, void(), override);
  MAKE_MOCK1(parse, commandline::CommandlineCommand::ReturnStatus(std::vector<std::string>&), override);
  MAKE_CONST_MOCK0(hasHelp, bool(), override);
};

TEST_CASE("Commandline Parser")  // NOLINT(readability-function-cognitive-complexity)
{
  SECTION("empty commandline") {
    std::string programName = "./sourcetrail";
    char* argv = programName.data();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(1, &argv);
    parser.parse();

    std::cout.rdbuf(oldBuf);
  }

  SECTION("empty commandline vector") {
    std::vector<std::string> args({"./sourcetrail"});

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str().empty());
    REQUIRE_FALSE(parser.runWithoutGUI());
    REQUIRE_FALSE(parser.exitApplication());
  }

  SECTION("version commandline") {
    std::vector<std::string> args({"./sourcetrail", "--version"});
    char* argv[] = {
        args[0].data(),
        args[1].data(),
    };

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(2, argv);
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str() == "Sourcetrail Version 2016.1\n");
  }

  SECTION("version commandline vector") {
    std::vector<std::string> args({"./sourcetrail", "--version"});

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str() == "Sourcetrail Version 2016.1\n");
  }

  SECTION("help commandline") {
    std::vector<std::string> args({"./sourcetrail", "--help"});

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    parser.preparse(args);
    parser.parse();

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str() == helpExpected);
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
    std::vector<std::string> args({"--project-file", "somewhere", "--project-file", "anothersomewhere"});

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

  SECTION("register command") {
    std::stringstream outStream;
    const auto& oldOutBuf = std::cout.rdbuf(outStream.rdbuf());
    std::stringstream errStream;
    const auto& oldErrBuf = std::cerr.rdbuf(errStream.rdbuf());

    commandline::CommandLineParser parser("2016.1");
    auto mocked = std::make_shared<MockCommand>("moc", "moc", &parser);
    {
      std::vector<std::string> args({"moc", "--help"});
      std::vector<std::string> moc_args = {"--help"};

      REQUIRE_CALL(*mocked, setup());
      REQUIRE_CALL(*mocked, parse(moc_args)).RETURN(commandline::CommandlineCommand::ReturnStatus::CMD_OK);
      parser.registerCommands({mocked});
      parser.preparse(args);
      parser.parse();
    }

    std::cout.rdbuf(oldOutBuf);
    std::cerr.rdbuf(oldErrBuf);

    REQUIRE(outStream.str().empty());
    REQUIRE(errStream.str().empty());
  }
}

TEST_CASE("Command Index")  // NOLINT(readability-function-cognitive-complexity)
{
  commandline::CommandLineParser mocParser("2016.1");
  SECTION("empty args") {
    auto args = std::vector<std::string>();
    commandline::CommandlineCommandIndex command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_QUIT);

    std::cout.rdbuf(oldBuf);

    REQUIRE_FALSE(redStream.str().empty());
  }

  SECTION("help args") {
    auto args = std::vector<std::string>{"--help"};
    commandline::CommandlineCommandIndex command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_QUIT);

    std::cout.rdbuf(oldBuf);

    REQUIRE_FALSE(redStream.str().empty());
    REQUIRE(command.hasHelp());
  }

  SECTION("incomplete args") {
    auto args = std::vector<std::string>{"--incomplete"};
    commandline::CommandlineCommandIndex command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_OK);
    REQUIRE(mocParser.getRefreshMode() == RefreshMode::REFRESH_UPDATED_AND_INCOMPLETE_FILES);

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str().empty());
  }

  SECTION("full args") {
    auto args = std::vector<std::string>{"--full"};
    commandline::CommandlineCommandIndex command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_OK);
    REQUIRE(mocParser.getRefreshMode() == RefreshMode::REFRESH_ALL_FILES);

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str().empty());
  }

  SECTION("shallow args") {
    auto args = std::vector<std::string>{"--shallow"};
    commandline::CommandlineCommandIndex command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_OK);
    REQUIRE(mocParser.getRefreshMode() == RefreshMode::REFRESH_UPDATED_FILES);

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str().empty());
  }

  SECTION("project-file args") {
    auto args = std::vector<std::string>{"--project-file", "something.srctrlprj"};
    commandline::CommandlineCommandIndex command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_OK);
    REQUIRE(mocParser.getProjectFilePath() == "something.srctrlprj");

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str().empty());
  }

  SECTION("multi project-file args") {
    auto args =
        std::vector<std::string>{"--project-file", "something.srctrlprj", "--project-file", "something_else.srctrlprj"};
    commandline::CommandlineCommandIndex command(&mocParser);
    command.setup();

    std::stringstream outStream;
    const auto& oldOutBuf = std::cout.rdbuf(outStream.rdbuf());
    std::stringstream errStream;
    const auto& oldErrBuf = std::cerr.rdbuf(errStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_FAILURE);
    REQUIRE(mocParser.getProjectFilePath().empty());

    std::cout.rdbuf(oldOutBuf);
    std::cerr.rdbuf(oldErrBuf);

    REQUIRE(outStream.str().empty());
    REQUIRE_FALSE(errStream.str().empty());
  }
}

TEST_CASE("Command Config")  // NOLINT(readability-function-cognitive-complexity)
{
  commandline::CommandLineParser mocParser("2016.1");
  SECTION("empty args") {
    auto args = std::vector<std::string>();
    commandline::CommandlineCommandConfig command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_QUIT);

    std::cout.rdbuf(oldBuf);

    REQUIRE_FALSE(redStream.str().empty());
  }

  SECTION("help args") {
    auto args = std::vector<std::string>{"--help"};
    commandline::CommandlineCommandConfig command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_QUIT);

    std::cout.rdbuf(oldBuf);

    REQUIRE_FALSE(redStream.str().empty());
    REQUIRE(command.hasHelp());
  }

  SECTION("indexer-threads args") {
    auto args = std::vector<std::string>{"--indexer-threads", "12"};
    commandline::CommandlineCommandConfig command(&mocParser);
    command.setup();

    std::stringstream redStream;
    const auto& oldBuf = std::cout.rdbuf(redStream.rdbuf());

    REQUIRE(command.parse(args) == commandline::CommandlineCommand::ReturnStatus::CMD_QUIT);

    std::cout.rdbuf(oldBuf);

    REQUIRE(redStream.str().empty());

    auto* pSettings = ApplicationSettings::getInstance().get();
    REQUIRE(pSettings->getIndexerThreadCount() == 12);
  }
}
