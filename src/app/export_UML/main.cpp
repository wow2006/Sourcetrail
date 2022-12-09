// STL
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <set>
// boost
#include <boost/program_options.hpp>
// Internal
#include "IndexerCommandCxx.h"
#include "IndexerCxx.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  std::filesystem::path projectPath;
  std::filesystem::path outputPath;
  try {
    po::options_description desc{"Options"};
    // clang-format off
    desc.add_options()
      ("help,h", "Help screen")
      ("project,p", po::value<std::filesystem::path>(&projectPath)->required(), "Project path")
      ("output,o", po::value<std::filesystem::path>(&outputPath)->required(), "SVG path");
    // clang-format on

    po::variables_map variablesMap;
    store(parse_command_line(argc, argv, desc), variablesMap);

    if (variablesMap.find("help") != variablesMap.end()) {
      std::cout << desc << '\n';
      return EXIT_SUCCESS;
    }

    notify(variablesMap);
  } catch (const po::error& ex) {
    std::cerr << ex.what() << '\n';
    return EXIT_FAILURE;
  }

  IndexerCxx indexer;
  /*
  IndexerCommandCxx indexer(
      FilePath(projectPath.parent_path().string()),
      std::set<FilePath>({ FilePath((projectPath.parent_path() / "main.cpp").string()) }),
      std::set<FilePathFilter>(),
      std::set<FilePathFilter>(),
      FilePath("."),
      std::vector<std::wstring>{}
  );
  */

  return EXIT_SUCCESS;
}
