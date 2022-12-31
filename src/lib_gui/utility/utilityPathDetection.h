#ifndef UTILITY_PATH_DETECTION_H
#define UTILITY_PATH_DETECTION_H

#include "utility/path_detector/CombinedPathDetector.h"

namespace utility {
std::shared_ptr<CombinedPathDetector> getJavaRuntimePathDetector();
std::shared_ptr<CombinedPathDetector> getJreSystemLibraryPathsDetector();
std::shared_ptr<CombinedPathDetector> getMavenExecutablePathDetector();

std::shared_ptr<CombinedPathDetector> getCxxVsHeaderPathDetector();
std::shared_ptr<CombinedPathDetector> getCxxHeaderPathDetector();
std::shared_ptr<CombinedPathDetector> getCxxFrameworkPathDetector();
}    // namespace utility


#endif    // UTILITY_PATH_DETECTION_H
