// catch2
#include "catch.hpp"
// internal
#include "ComponentFactory.h"
#include "ConsoleLogger.h"
#include "helper/Mocks.h"

TEST_CASE("ComponentFactory", "[lib,app]") {
  auto pConsoleLogger = std::make_shared<ConsoleLogger>();
  pConsoleLogger->setLogLevel(Logger::LOG_ALL);

  auto pLogManager = LogManager::getInstance();
  pLogManager->addLogger(pConsoleLogger);
  pLogManager->setLoggingEnabled(true);

  MockedViewFactory mockedViewFactory;
  ComponentFactory componentFactory(&mockedViewFactory, nullptr);

  SECTION("createActivationComponent") {
    auto component = componentFactory.createActivationComponent();
    REQUIRE(component);
  }

  MainViewMocked mockedMainView(&mockedViewFactory, nullptr);
  SECTION("createBookmarkComponent") {
    REQUIRE_CALL(mockedViewFactory, createBookmarkView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createBookmarkComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createCodeComponent") {
    REQUIRE_CALL(mockedViewFactory, createCodeView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createCodeComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createCustomTrailComponent") {
    REQUIRE_CALL(mockedViewFactory, createCustomTrailView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createCustomTrailComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createErrorComponent") {
    REQUIRE_CALL(mockedViewFactory, createErrorView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createErrorComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createGraphComponent") {
    REQUIRE_CALL(mockedViewFactory, createGraphView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createGraphComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createRefreshComponent") {
    REQUIRE_CALL(mockedViewFactory, createRefreshView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createRefreshComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createScreenSearchComponent") {
    REQUIRE_CALL(mockedViewFactory, createScreenSearchView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createScreenSearchComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createSearchComponent") {
    REQUIRE_CALL(mockedViewFactory, createSearchView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createSearchComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createStatusBarComponent") {
    REQUIRE_CALL(mockedViewFactory, createStatusBarView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createStatusBarComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createStatusComponent") {
    REQUIRE_CALL(mockedViewFactory, createStatusView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createStatusComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createTabsComponent") {
    REQUIRE_CALL(mockedViewFactory, createTabsView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createTabsComponent(&mockedMainView, nullptr);
    REQUIRE(component);
  }

  SECTION("createTooltipComponent") {
    REQUIRE_CALL(mockedViewFactory, createTooltipView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createTooltipComponent(&mockedMainView);
    REQUIRE(component);
  }

  SECTION("createUndoRedoComponent") {
    REQUIRE_CALL(mockedViewFactory, createUndoRedoView(_))
      .RETURN(nullptr);

    auto component = componentFactory.createUndoRedoComponent(&mockedMainView);
    REQUIRE(component);
  }
}