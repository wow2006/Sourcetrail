// STL
#include <cstdlib>
#include <iostream>
#include <filesystem>
// boost
#include <boost/program_options.hpp>


namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  std::filesystem::path projectPath;
  try {
    po::options_description desc{"Options"};
    // clang-format off
    desc.add_options()
      ("help,h", "Help screen")
      ("project-file-path,p", po::value<std::filesystem::path>(&projectPath)->required(), "Project path");
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

  std::cout << projectPath << '\n';
  return EXIT_SUCCESS;
}
