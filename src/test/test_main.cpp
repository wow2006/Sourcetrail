#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() function

#include "catch.hpp"
// IMPORTANT NOTE: removed signal listener for "EXCEPTION_ACCESS_VIOLATION" from catch source code
// because it interferes with the jni interface that emits such a signal on purpose

#ifdef GUI_ENABLED
#include "ApplicationSettings.h"
#include "language_packages.h"
#include "utilityPathDetection.h"

struct EventListener final : Catch::TestEventListenerBase {
  using TestEventListenerBase::TestEventListenerBase;  // inherit constructor

  void testRunStarting([[maybe_unused]] const Catch::TestRunInfo& testRunInfo) override {
#ifdef __linux__
    if (!ApplicationSettings::getInstance()->load(FilePath("data/ApplicationSettings.xml"))) {
      std::cout << "no settings" << std::endl;
      return;
    }
#else
    ApplicationSettings::getInstance()->load(FilePath(L"data/TestSettings.xml"));
#endif

#if BUILD_JAVA_LANGUAGE_PACKAGE
    if (ApplicationSettings::getInstance()->getJavaPath().empty()) {
      std::shared_ptr<PathDetector> pathDetector = utility::getJavaRuntimePathDetector();
      const std::vector<FilePath> paths = pathDetector->getPaths();
      if (!paths.empty()) {
        ApplicationSettings::getInstance()->setJavaPath(paths.front());
        std::cout << "Java path written to settings: " << ApplicationSettings::getInstance()->getJavaPath().str()
                  << std::endl;
      } else {
        std::cout << "no Java" << std::endl;
      }
    } else {
      std::cout << "Java path read form settings: " << ApplicationSettings::getInstance()->getJavaPath().str()
                << std::endl;
    }
#endif
  }
};

CATCH_REGISTER_LISTENER(EventListener)
#endif