// STL
#include <cstdlib>
#include <iostream>
#include <filesystem>
// boost
#include <boost/program_options.hpp>


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

    po::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
      std::cout << desc << '\n';
      return EXIT_SUCCESS;
    }

    notify(vm);
  } catch (const po::error &ex) {
    std::cerr << ex.what() << '\n';
    return EXIT_FAILURE;
  }

  std::cout << projectPath << ", " << outputPath << '\n';
  return EXIT_SUCCESS;
}
