// catch
#include "catch.hpp"
//
#include "trompeloeil.hpp"

#include "Logger.h"
#include <thread>

struct MockedLogger : Logger {
  MockedLogger() : Logger("mocked") {}

  ~MockedLogger() override = default;  

  MAKE_MOCK1(logInfo,    void(const LogMessage&), override); 
  MAKE_MOCK1(logWarning, void(const LogMessage&), override); 
  MAKE_MOCK1(logError,   void(const LogMessage&), override); 
};

TEST_CASE("Logger", "[lib,utility,logging]") {
  MockedLogger mockedLogger;

  SECTION("type") {
    REQUIRE(mockedLogger.getType() == "mocked");
  }

  SECTION("Log Level") {
    REQUIRE(mockedLogger.getLogLevel() == Logger::LOG_ALL);
    REQUIRE(mockedLogger.isLogLevel(Logger::LOG_ALL));
    REQUIRE(mockedLogger.isLogLevel(Logger::LOG_INFOS));
    REQUIRE(mockedLogger.isLogLevel(Logger::LOG_WARNINGS));
    REQUIRE(mockedLogger.isLogLevel(Logger::LOG_ERRORS));

    for(auto level : {
      Logger::LogLevel::LOG_INFOS,
      Logger::LogLevel::LOG_WARNINGS,
      Logger::LogLevel::LOG_ERRORS,}) {
      mockedLogger.setLogLevel(level);
      REQUIRE(mockedLogger.isLogLevel(level));
      REQUIRE(mockedLogger.getLogLevel() == level);
    }
  }

  SECTION("Log Level info") {
    mockedLogger.setLogLevel(Logger::LogLevel::LOG_INFOS);
    REQUIRE(mockedLogger.isLogLevel(Logger::LOG_INFOS));
    REQUIRE_FALSE(mockedLogger.isLogLevel(Logger::LOG_WARNINGS));
    REQUIRE_FALSE(mockedLogger.isLogLevel(Logger::LOG_ERRORS));
  }

  SECTION("Log Level warning") {
    mockedLogger.setLogLevel(Logger::LogLevel::LOG_WARNINGS);
    REQUIRE_FALSE(mockedLogger.isLogLevel(Logger::LOG_INFOS));
    REQUIRE(mockedLogger.isLogLevel(Logger::LOG_WARNINGS));
    REQUIRE_FALSE(mockedLogger.isLogLevel(Logger::LOG_ERRORS));
  }

  SECTION("Log Level error") {
    mockedLogger.setLogLevel(Logger::LogLevel::LOG_ERRORS);
    REQUIRE_FALSE(mockedLogger.isLogLevel(Logger::LOG_INFOS));
    REQUIRE_FALSE(mockedLogger.isLogLevel(Logger::LOG_WARNINGS));
    REQUIRE(mockedLogger.isLogLevel(Logger::LOG_ERRORS));
  }

  auto message = LogMessage(L"message", "file", "func", 0, std::tm{}, std::this_thread::get_id());
  SECTION("onInfo") {
    REQUIRE_CALL(mockedLogger, logInfo(ANY(LogMessage)))
      .TIMES(AT_LEAST(1));
    
    mockedLogger.logInfo(message);
  }

  SECTION("onWarning") {
    REQUIRE_CALL(mockedLogger, logWarning(ANY(LogMessage)))
      .TIMES(AT_LEAST(1));
    
    mockedLogger.logWarning(message);
  }

  SECTION("onError") {
    REQUIRE_CALL(mockedLogger, logError(ANY(LogMessage)))
      .TIMES(AT_LEAST(1));
    
    mockedLogger.logError(message);
  }
}