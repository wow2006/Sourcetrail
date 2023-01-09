#pragma once

#include "utility.h"
#include "utilityString.h"

namespace boost::program_options {
class variables_map;
class options_description;
}    // namespace boost::program_options

namespace commandline {

void parseConfigFile(boost::program_options::variables_map& vm, boost::program_options::options_description& options);

std::vector<utility::file::FilePath> extractPaths(const std::vector<std::string>& vector);

}    // namespace commandline
