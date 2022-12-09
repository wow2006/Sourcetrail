// STL
#include <filesystem>
#include <iostream>
// Boost
#include <boost/process.hpp>
// Catch2
#include <catch.hpp>

namespace bp = boost::process;
namespace fs = std::filesystem;

SCENARIO("Simple helloWorld project", "[functionality]") {
  std::cout << "Export_UML" << Export_UML << '\n';
  GIVEN("The exportUML process exists") {
    constexpr auto processPath = "../app/exportUML";

    std::error_code errorCode;
    REQUIRE(fs::exists(processPath, errorCode));

    AND_GIVEN("The helloWorld project file exists") {
      const auto projectPath = fs::path("data/helloWorld/helloWorld.srctrlprj");
      REQUIRE(fs::exists(projectPath, errorCode));

      AND_GIVEN("The project files are exists") {
        // TODO: Check the project file is valid
        // const auto project = Project(projectPath);
        // REQUIRE(project.isValid());

        WHEN("Pass the helloWorld project path to the process") {
          constexpr auto svgPath = "output.svg";

          bp::ipstream errorStream;
          bp::ipstream outStream;

          auto childProcess = bp::child(bp::exe = processPath,
                                        bp::args =
                                            {
                                                "--project",
                                                projectPath.string(),
                                                "--output",
                                                svgPath,
                                            },
                                        bp::std_out > errorStream, bp::std_err > outStream);
          childProcess.wait(errorCode);
          REQUIRE_FALSE(errorCode);

          THEN("A SVG file will be exported") { REQUIRE(fs::exists(svgPath, errorCode)); }
        }
      }
    }
  }
}
