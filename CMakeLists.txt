# ${CMAKE_SOURCE_DIR}/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(
  Sourcetrail
  DESCRIPTION "open-source cross-platform source explorer"
  HOMEPAGE_URL ""
  LANGUAGES C CXX
)

if(WIN32 AND (CMAKE_GENERATOR STREQUAL "Ninja"))
  set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
endif()

set(BUILD_UNIT_TESTS              ON  CACHE BOOL "Build unit tests")
set(BUILD_FUNC_TESTS              OFF CACHE BOOL "Build func tests")
set(BUILD_EXPORT_UML              OFF CACHE BOOL "Build export_uml app")

set(BUILD_CXX_LANGUAGE_PACKAGE    OFF CACHE BOOL "Add C and C++ support to the Sourcetrail indexer.")
set(BUILD_JAVA_LANGUAGE_PACKAGE   OFF CACHE BOOL "Add Java support to the Sourcetrail indexer.")
set(BUILD_PYTHON_LANGUAGE_PACKAGE OFF CACHE BOOL "Add Python support to the Sourcetrail indexer.")
set(ENABLE_MEMORY_ASAN            OFF CACHE BOOL "Build with memory sanitizers")
set(ENABLE_ADDRESS_ASAN           OFF CACHE BOOL "Build with address sanitizers")
set(ENABLE_DOXYGEN                OFF CACHE BOOL "Build the doxygen")

set(TREAT_WARNINGS_AS_ERRORS      OFF CACHE BOOL "Treat compiler warnings as errors")
set(DOCKER_BUILD                  OFF CACHE BOOL "Build runs in Docker")
set(BUILD_COVERAGE                OFF CACHE BOOL "Generate a coverage report")
set(BUILD_REPORT                  OFF CACHE BOOL "Export a building time report")

include(cmake/add_files.cmake)
include(cmake/compiler_warnings.cmake)
include(cmake/create_source_groups.cmake)
include(cmake/licenses.cmake)
include(cmake/version.cmake)
include(cmake/version_setup.cmake)
include(cmake/doxygen.cmake)

if(ENABLE_MEMORY_ASAN OR ENABLE_ADDRESS_ASAN)
  if(ENABLE_MEMORY_ASAN AND ENABLE_ADDRESS_ASAN)
    message(FATAL_ERROR "Cannot enable both memory and address sanitizers")
  endif()

  include(cmake/sanitizers.cmake)
endif()

if(BUILD_UNIT_TESTS OR BUILD_FUNC_TESTS)
  enable_testing()
endif()

if(BUILD_REPORT)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS};-ftime-report")
  else()
    message(FATAL_ERROR "Build report is not supported in selected compiler ${CMAKE_CXX_COMPILER_ID}")
  endif()
endif()

if(BUILD_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS};-fprofile-arcs;-ftest-coverage;-fPIC;-O0;-g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS};-fprofile-arcs")

    configure_file(
      ${CMAKE_SOURCE_DIR}/cmake/coverage.sh.in
      ${CMAKE_BINARY_DIR}/coverage.sh
    )
  else()
    message(FATAL_ERROR "Coverage is not supported in selected compiler ${CMAKE_CXX_COMPILER_ID}")
  endif()
endif()

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD          17)
set(CMAKE_C_EXTENSIONS        OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(src)
