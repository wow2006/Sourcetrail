#ifndef UTILITY_CXX_HEADER_DETECTION_H
#define UTILITY_CXX_HEADER_DETECTION_H

#include <string>
#include <vector>

#include "ApplicationArchitectureType.h"
namespace utility::file {
class FilePath;
} // namespace class utility::file

namespace utility
{
std::vector<std::wstring> getCxxHeaderPaths(const std::string& compilerName);

std::vector<utility::file::FilePath> getWindowsSdkHeaderSearchPaths(ApplicationArchitectureType architectureType);
utility::file::FilePath getWindowsSdkRootPathUsingRegistry(
	ApplicationArchitectureType architectureType, const std::string& sdkVersion);
}	 // namespace utility

#endif	  // UTILITY_CXX_HEADER_DETECTION_H
