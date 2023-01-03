# ${CMAKE_SOURCE_DIR}/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(Sourcetrail C CXX)

if(WIN32 AND (CMAKE_GENERATOR STREQUAL "Ninja"))
  set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
endif()

set(BUILD_CXX_LANGUAGE_PACKAGE
    OFF
    CACHE BOOL "Add C and C++ support to the Sourcetrail indexer.")
set(BUILD_JAVA_LANGUAGE_PACKAGE
    OFF
    CACHE BOOL "Add Java support to the Sourcetrail indexer.")
set(BUILD_PYTHON_LANGUAGE_PACKAGE
    OFF
    CACHE BOOL "Add Python support to the Sourcetrail indexer.")
set(ENABLE_MEMORY_ASAN
    OFF
    CACHE BOOL "Build with memory sanitizers")
set(ENABLE_ADDRESS_ASAN
    OFF
    CACHE BOOL "Build with address sanitizers")
set(DOCKER_BUILD
    OFF
    CACHE BOOL "Build runs in Docker")
set(TREAT_WARNINGS_AS_ERRORS
    OFF
    CACHE BOOL "Treat compiler warnings as errors")
set(BUILD_COVERAGE
    OFF
    CACHE BOOL "Generate a coverage report")
set(BUILD_TEST
    ON
    CACHE BOOL "Build unit tests")
set(BUILD_FUNC
    OFF
    CACHE BOOL "Build functionality tests")
set(BUILD_BENCHMARK
    OFF
    CACHE BOOL "Build benchmarks")

include(cmake/compiler_warnings.cmake)
include(cmake/add_files.cmake)
include(cmake/create_source_groups.cmake)
include(cmake/version.cmake)
include(cmake/version_setup.cmake)
include(cmake/licenses.cmake)

if(ENABLE_MEMORY_ASAN OR ENABLE_ADDRESS_ASAN)
  if(ENABLE_MEMORY_ASAN AND ENABLE_ADDRESS_ASAN)
    message(FATAL_ERROR "Cannot enable both memory and address sanitizers")
  endif()

  include(cmake/sanitizers.cmake)
endif()

# prohibit in-source-builds
if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  message(STATUS "In-source-builds are not allowed")
  message(
    STATUS "Clean your source directory (e.g. delete the CMakeCache.txt file)")
  message(
    FATAL_ERROR "Please create a separate build directory and call CMake again")
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER_LAUNCHER)
  # speed up recompiling on unix with ccache
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    message(STATUS "ccache found")
    # Support Unix Makefiles and Ninja
    set(CMAKE_CXX_COMPILER_LAUNCHER
        "${CCACHE_PROGRAM}"
        CACHE STRING "Compiler launcher for CXX")
  endif()
endif()

# Variables --------------------------------------------------------------------
if(WIN32)
  set(PLATFORM_INCLUDE "includesWindows.h")
elseif(APPLE)
  set(PLATFORM_INCLUDE "includesMac.h")
else()
  set(PLATFORM_INCLUDE "includesLinux.h")
endif()

set(BASH "")
if(WIN32)
  execute_process(COMMAND CMD /c where bash OUTPUT_VARIABLE BASH)
  string(REGEX REPLACE "\n$" "" BASH "${BASH}")
  message("bash: '${BASH}'")
endif()

# Project ----------------------------------------------------------------------
if(UNIX AND NOT APPLE)
  set(CMAKE_SKIP_BUILD_RPATH FALSE)
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/lib/:$$ORIGIN/lib/")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  add_compile_options(-fcolor-diagnostics)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
endif()

if(BUILD_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0 -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs")

    configure_file(
      ${CMAKE_SOURCE_DIR}/cmake/coverage.sh.in ${CMAKE_BINARY_DIR}/coverage.sh
      FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)
  else()
    message(
      FATAL_ERROR
        "Coverage is not supported in selected compiler ${CMAKE_CXX_COMPILER_ID}"
    )
  endif()
endif()

# Packages ---------------------------------------------------------------------
find_package(fmt      REQUIRED)
find_package(range-v3 REQUIRED)
# Clang ------------------------------------------------------------------------
if(BUILD_CXX_LANGUAGE_PACKAGE)
  find_package(Clang REQUIRED)

  if(LLVM_FOUND)
    message(STATUS "Found LLVM ${LLVM_VERSION}")
  endif()

  if(UNIX)
    set(LLVM_CONFIGURATION_TYPES ".")
  endif()

  set(CLANG_COMPILER_HEADER_SEARCH_PATH "")
  foreach(LLVM_CONFIGURATION_TYPE ${LLVM_CONFIGURATION_TYPES})
    if(CLANG_COMPILER_HEADER_SEARCH_PATH STREQUAL "")
      set(_CLANG_HEADERS_SEARCH_LIST
          "${LLVM_BINARY_DIR}/${LLVM_CONFIGURATION_TYPE}/lib/clang/${LLVM_VERSION}/include"
          "${LLVM_BINARY_DIR}/${LLVM_CONFIGURATION_TYPE}/lib64/clang/${LLVM_VERSION}/include"
      )
      foreach(_CLANG_HEADER_PATH ${_CLANG_HEADERS_SEARCH_LIST})
        if(EXISTS ${_CLANG_HEADER_PATH})
          set(CLANG_COMPILER_HEADER_SEARCH_PATH ${_CLANG_HEADER_PATH})
          break()
        endif()
      endforeach()

      message(
        STATUS
          "Trying to find Clang compiler headers in '${LLVM_CONFIGURATION_TYPE}' build config in directory '${CLANG_COMPILER_HEADER_SEARCH_PATH}'."
      )
      if(EXISTS ${CLANG_COMPILER_HEADER_SEARCH_PATH})
        message(
          STATUS "Found headers for '${LLVM_CONFIGURATION_TYPE}' build config.")
        file(
          GLOB_RECURSE CLANG_COMPILER_HEADER_PATHS
          RELATIVE "${CLANG_COMPILER_HEADER_SEARCH_PATH}"
          "${CLANG_COMPILER_HEADER_SEARCH_PATH}/*")
        foreach(CLANG_COMPILER_HEADER_PATH ${CLANG_COMPILER_HEADER_PATHS})
          configure_file(
            "${CLANG_COMPILER_HEADER_SEARCH_PATH}/${CLANG_COMPILER_HEADER_PATH}"
            "${CMAKE_SOURCE_DIR}/bin/app/data/cxx/include/${CLANG_COMPILER_HEADER_PATH}"
            COPYONLY)
        endforeach()
      else()
        set(CLANG_COMPILER_HEADER_SEARCH_PATH "")
      endif()
    endif()
  endforeach()

  if(CLANG_COMPILER_HEADER_SEARCH_PATH STREQUAL "")
    message(
      FATAL_ERROR "Unable to copy Clang compiler headers from clang build dir.")
  endif()
endif()
# Boost ------------------------------------------------------------------------
set(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_LIBS
    ON
    CACHE BOOL "Set to ON to force the use of the static libraries.")
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(
  Boost 1.67
  COMPONENTS system program_options filesystem date_time
  REQUIRED)

# Qt ---------------------------------------------------------------------------
set(QT_MIN_VERSION "5.12.0")
set(QT_MIN_VERSION_HEX 0x051200)
find_package(
  Qt5 ${QT_MIN_VERSION}
  COMPONENTS Widgets PrintSupport Network Svg
  REQUIRED)

if(WIN32)
  find_package(
    Qt5 ${QT_MIN_VERSION}
    COMPONENTS WinExtras
    REQUIRED)
endif()

if(Qt5Widgets_FOUND)
  message(STATUS "Found Qt ${Qt5Widgets_VERSION_STRING}")

  # FIX: Qt was built with -reduce-relocations
  if(Qt5_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  endif()

  # The following define makes your compiler emit warnings if you use any
  # feature of Qt which as been marked as deprecated (the exact warnings depend
  # on your compiler). Please consult the documentation of the deprecated API in
  # order to know how to port your code away from it.
  add_definitions(-DQT_DEPRECATED_WARNINGS)

  # You can also make your code fail to compile if you use deprecated APIs. In
  # order to do so, uncomment the following line. You can also select to disable
  # deprecated APIs only up to a certain version of Qt. DEFINES +=
  # QT_DISABLE_DEPRECATED_BEFORE=${QT_MIN_VERSION_HEX}    # disables all the
  # APIs deprecated at or before the specified Qt version
  add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=${QT_MIN_VERSION_HEX})
endif()

if(BUILD_TEST OR BUILD_FUNC)
  enable_testing()
endif()

add_subdirectory(src)
