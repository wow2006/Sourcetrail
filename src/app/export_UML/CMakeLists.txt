# ${CMAKE_SOURCE_DIR}/src/app/export_UML/CMakeLists.txt
add_executable(
  exportUML
  main.cpp
)

target_link_libraries(
  exportUML
  PRIVATE
  Qt5::Core
  Boost::program_options
)

set_target_properties(
  exportUML
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/app"
)

set_project_warnings(exportUML)

