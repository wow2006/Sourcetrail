#include "includes.h"

#include "language_packages.h"

#include "AppPath.h"
#include "ApplicationSettings.h"
#include "FileLogger.h"
#include "InterprocessIndexer.h"
#include "LanguagePackageManager.h"
#include "LogManager.h"
#include "logging.h"

#if BUILD_CXX_LANGUAGE_PACKAGE
#  include "LanguagePackageCxx.h"
#endif    // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE
#  include "LanguagePackageJava.h"
#endif    // BUILD_JAVA_LANGUAGE_PACKAGE

void setupLogging(const FilePath& logFilePath) {
  auto* pLogManager = LogManager::getInstance().get();

  auto pFileLogger = std::make_shared<FileLogger>();
  pFileLogger->setLogFilePath(logFilePath);
  pFileLogger->setLogLevel(Logger::LOG_ALL);
  pLogManager->addLogger(pFileLogger);
}

void suppressCrashMessage() {
#ifdef WINDOWS
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#endif    // WINDOWS
}

int main(int argc, char* argv[]) {
  int processId = -1;
  std::string instanceUuid;
  std::string appPath;
  std::string userDataPath;
  std::string logFilePath;

  if(argc >= 2) {
    processId = std::stoi(argv[1]);
  }

  if(argc >= 3) {
    instanceUuid = argv[2];
  }

  if(argc >= 4) {
    appPath = argv[3];
  }

  if(argc >= 5) {
    userDataPath = argv[4];
  }

  if(argc >= 6) {
    logFilePath = argv[5];
  }

  AppPath::setSharedDataDirectoryPath(FilePath(appPath));
  UserPaths::setUserDataDirectoryPath(FilePath(userDataPath));

  if(!logFilePath.empty()) {
    setupLogging(FilePath(logFilePath));
  }

  suppressCrashMessage();

  auto* pAppSettings = ApplicationSettings::getInstance().get();
  pAppSettings->load((UserPaths::getAppSettingsFilePath()));
  LogManager::getInstance()->setLoggingEnabled(pAppSettings->getLoggingEnabled());

  LOG_INFO(L"sharedDataPath: " + AppPath::getSharedDataDirectoryPath().wstr());
  LOG_INFO(L"userDataPath: " + UserPaths::getUserDataDirectoryPath().wstr());


#if BUILD_CXX_LANGUAGE_PACKAGE
  LanguagePackageManager::getInstance()->addPackage(std::make_shared<LanguagePackageCxx>());
#endif    // BUILD_CXX_LANGUAGE_PACKAGE

#if BUILD_JAVA_LANGUAGE_PACKAGE
  LanguagePackageManager::getInstance()->addPackage(std::make_shared<LanguagePackageJava>());
#endif    // BUILD_JAVA_LANGUAGE_PACKAGE

  InterprocessIndexer indexer(instanceUuid, static_cast<Id>(processId));
  indexer.work();

  return 0;
}
