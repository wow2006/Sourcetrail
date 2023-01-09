#include "includes.h"

#include <csignal>
#include <iostream>

#include "language_packages.h"

#include "Application.h"
#include "ApplicationSettings.h"
#include "ApplicationSettingsPrefiller.h"
#include "CommandLineParser.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "LanguagePackageManager.h"
#include "LogManager.h"
#include "MessageIndexingInterrupted.h"
#include "MessageLoadProject.h"
#include "MessageStatus.h"
#include "QtApplication.h"
#include "QtCoreApplication.h"
#include "QtNetworkFactory.h"
#include "QtViewFactory.h"
#include "ResourcePaths.h"
#include "ScopedFunctor.h"
#include "SourceGroupFactory.h"
#include "SourceGroupFactoryModuleCustom.h"
#include "UserPaths.h"
#include "Version.h"
#include "logging.h"
#include "productVersion.h"
#include "utility.h"
#include "utilityApp.h"
#include "utilityQt.h"

#if BUILD_CXX_LANGUAGE_PACKAGE
#  include "LanguagePackageCxx.h"
#  include "SourceGroupFactoryModuleCxx.h"
#endif    // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE
#  include "LanguagePackageJava.h"
#  include "SourceGroupFactoryModuleJava.h"
#endif    // BUILD_JAVA_LANGUAGE_PACKAGE

#if BUILD_PYTHON_LANGUAGE_PACKAGE
#  include "SourceGroupFactoryModulePython.h"
#endif    // BUILD_PYTHON_LANGUAGE_PACKAGE

void signalHandler(int /*signum*/) {
  std::cout << "interrupt indexing" << std::endl;
  MessageIndexingInterrupted().dispatch();
}

void setupLogging() {
  auto* pLogManager = LogManager::getInstance().get();

  auto pConsoleLogger = std::make_shared<ConsoleLogger>();
  pConsoleLogger->setLogLevel(Logger::LOG_ALL);
  pLogManager->addLogger(pConsoleLogger);

  auto pFileLogger = std::make_shared<FileLogger>();
  pFileLogger->setLogLevel(Logger::LOG_ALL);
  pFileLogger->deleteLogFiles(FileLogger::generateDatedFileName(L"log", L"", -30));
  pLogManager->addLogger(pFileLogger);
}

void addLanguagePackages() {
  SourceGroupFactory::getInstance()->addModule(std::make_shared<SourceGroupFactoryModuleCustom>());

#if BUILD_CXX_LANGUAGE_PACKAGE
  SourceGroupFactory::getInstance()->addModule(std::make_shared<SourceGroupFactoryModuleCxx>());
#endif    // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE
  SourceGroupFactory::getInstance()->addModule(std::make_shared<SourceGroupFactoryModuleJava>());
#endif    // BUILD_JAVA_LANGUAGE_PACKAGE

#if BUILD_PYTHON_LANGUAGE_PACKAGE
  SourceGroupFactory::getInstance()->addModule(std::make_shared<SourceGroupFactoryModulePython>());
#endif    // BUILD_PYTHON_LANGUAGE_PACKAGE

#if BUILD_CXX_LANGUAGE_PACKAGE
  LanguagePackageManager::getInstance()->addPackage(std::make_shared<LanguagePackageCxx>());
#endif    // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE
  LanguagePackageManager::getInstance()->addPackage(std::make_shared<LanguagePackageJava>());
#endif    // BUILD_JAVA_LANGUAGE_PACKAGE
}

int main(int argc, char* argv[]) {
  QCoreApplication::addLibraryPath(QStringLiteral("."));
#ifdef WINDOWS
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
  if(utility::getOsType() == OS_LINUX && std::getenv("SOURCETRAIL_VIA_SCRIPT") == nullptr &&
     !utility::file::FilePath(QCoreApplication::applicationDirPath().toStdWString() + L"/../share").exists()) {
    std::cout << "ERROR: Please run Sourcetrail via the Sourcetrail.sh script!" << std::endl;
  }
#ifdef WINDOWS
#pragma warning(pop)
#endif

  QApplication::setApplicationName(QStringLiteral("Sourcetrail"));

  if(utility::getOsType() != OS_LINUX) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
  }

  Version version(VERSION_YEAR, VERSION_MINOR, VERSION_COMMIT, GIT_COMMIT_HASH);
  QApplication::setApplicationVersion(version.toDisplayString().c_str());

  MessageStatus(
      std::wstring(L"Starting Sourcetrail ") +
      (utility::getApplicationArchitectureType() == APPLICATION_ARCHITECTURE_X86_32 ? L"32" : L"64") +
      L" bit, " + L"version " + version.toDisplayWString())
      .dispatch();

  commandline::CommandLineParser commandLineParser(version.toDisplayString());
  commandLineParser.preparse(argc, argv);
  if(commandLineParser.exitApplication()) {
    return 0;
  }

  setupPlatform(argc, argv);

  if(commandLineParser.runWithoutGUI()) {
    // headless Sourcetrail
    QtCoreApplication qtApp(argc, argv);

    setupApp(argc, argv);

    setupLogging();

    lib::app::Application::createInstance(version, nullptr, nullptr);
    ScopedFunctor f([]() { lib::app::Application::destroyInstance(); });

    ApplicationSettingsPrefiller::prefillPaths(ApplicationSettings::getInstance().get());
    addLanguagePackages();

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGABRT, signalHandler);

    commandLineParser.parse();

    if(commandLineParser.exitApplication()) {
      return 0;
    }

    if(commandLineParser.hasError()) {
      std::wcout << commandLineParser.getError() << std::endl;
    } else {
      MessageLoadProject(commandLineParser.getProjectFilePath(),
                         false,
                         commandLineParser.getRefreshMode(),
                         commandLineParser.getShallowIndexingRequested())
          .dispatch();
    }

    return QtCoreApplication::exec();
  }

#ifdef WINDOWS
  {
    HWND consoleWnd = GetConsoleWindow();
    DWORD dwProcessId;
    GetWindowThreadProcessId(consoleWnd, &dwProcessId);
    if(GetCurrentProcessId() == dwProcessId) {
      // Sourcetrail has not been started from console and thus has it's own console
      ShowWindow(consoleWnd, SW_HIDE);
    }
  }
#endif
  QtApplication qtApp(argc, argv);

  setupApp(argc, argv);

  setupLogging();

  qtApp.setAttribute(Qt::AA_UseHighDpiPixmaps);

  QtViewFactory viewFactory;
  QtNetworkFactory networkFactory;

  lib::app::Application::createInstance(version, &viewFactory, &networkFactory);
  ScopedFunctor destroyApplicationAtExist([]() { lib::app::Application::destroyInstance(); });

  ApplicationSettingsPrefiller::prefillPaths(ApplicationSettings::getInstance().get());
  addLanguagePackages();

  utility::loadFontsFromDirectory(ResourcePaths::getFontsDirectoryPath(), L".otf");
  utility::loadFontsFromDirectory(ResourcePaths::getFontsDirectoryPath(), L".ttf");

  if(commandLineParser.hasError()) {
    lib::app::Application::getInstance()->handleDialog(commandLineParser.getError());
  } else {
    MessageLoadProject(commandLineParser.getProjectFilePath(), false, REFRESH_NONE).dispatch();
  }

  return qtApp.exec();
}
