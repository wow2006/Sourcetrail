# ${CMAKE_SOURCE_DIR}/src/test/functionality/CMakeLists.txt
add_executable(
  ExportUMLTest
  ExportUMLTest.cpp
  $<TARGET_OBJECTS:test_main>
)

target_include_directories(
  ExportUMLTest
  SYSTEM PUBLIC
  ${CMAKE_SOURCE_DIR}/src/external/catch/
)

target_link_libraries(
  ExportUMLTest
  PRIVATE
  Sourcetrail_lib
  Sourcetrail_lib_utility
)

target_compile_definitions(
  ExportUMLTest
  PUBLIC Export_UML="$<TARGET_FILE:exportUML>"
)

set_target_properties(
  ExportUMLTest
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
)

add_dependencies(
  ExportUMLTest
  CopyDataToTestsDir
  ExtractHelloWorld
  exportUML
)

add_test(
  NAME ExportUMLTest
  COMMAND CommandlineTestSuite
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
)

