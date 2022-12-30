# ${CMAKE_SOURCE_DIR}/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

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
    ON
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
  message(STATUS "Clean your source directory (e.g. delete the CMakeCache.txt file)")
  message(FATAL_ERROR "Please create a separate build directory and call CMake again")
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

set(PROJECT_NAME Sourcetrail)

set(LIB_UTILITY_PROJECT_NAME "${PROJECT_NAME}_lib_utility")
set(LIB_GUI_PROJECT_NAME "${PROJECT_NAME}_lib_gui")
set(LIB_CXX_PROJECT_NAME "${PROJECT_NAME}_lib_cxx")
set(LIB_JAVA_PROJECT_NAME "${PROJECT_NAME}_lib_java")
set(LIB_PYTHON_PROJECT_NAME "${PROJECT_NAME}_lib_python")
set(LIB_PROJECT_NAME "${PROJECT_NAME}_lib")
set(TEST_PROJECT_NAME "${PROJECT_NAME}_test")
set(FUNC_PROJECT_NAME "${PROJECT_NAME}_func")

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
  string(
    REGEX
    REPLACE "\n$"
            ""
            BASH
            "${BASH}")
endif()

message("bash: '${BASH}'")

# Project ----------------------------------------------------------------------

project(${PROJECT_NAME})

# set Standard build type to Release
set(CMAKE_BUILD_TYPE_INIT "Release")

# RPATH
if(UNIX AND NOT APPLE)
  set(CMAKE_SKIP_BUILD_RPATH FALSE)
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/lib/:$$ORIGIN/lib/")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)

if(BUILD_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0 -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs")

    configure_file(
      ${CMAKE_SOURCE_DIR}/cmake/coverage.sh.in
      ${CMAKE_BINARY_DIR}/coverage.sh
      FILE_PERMISSIONS
      OWNER_EXECUTE
      OWNER_WRITE
      OWNER_READ)
  else()
    message(FATAL_ERROR "Coverage is not supported in selected compiler ${CMAKE_CXX_COMPILER_ID}")
  endif()
endif()

# Settings ---------------------------------------------------------------------

# FIXME: necessary to fix build in Docker
if(DOCKER_BUILD)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif()

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
          "${LLVM_BINARY_DIR}/${LLVM_CONFIGURATION_TYPE}/lib64/clang/${LLVM_VERSION}/include")
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
        message(STATUS "Found headers for '${LLVM_CONFIGURATION_TYPE}' build config.")
        file(
          GLOB_RECURSE CLANG_COMPILER_HEADER_PATHS
          RELATIVE "${CLANG_COMPILER_HEADER_SEARCH_PATH}"
          "${CLANG_COMPILER_HEADER_SEARCH_PATH}/*")
        foreach(CLANG_COMPILER_HEADER_PATH ${CLANG_COMPILER_HEADER_PATHS})
          configure_file("${CLANG_COMPILER_HEADER_SEARCH_PATH}/${CLANG_COMPILER_HEADER_PATH}"
                         "${CMAKE_SOURCE_DIR}/bin/app/data/cxx/include/${CLANG_COMPILER_HEADER_PATH}" COPYONLY)
        endforeach()
      else()
        set(CLANG_COMPILER_HEADER_SEARCH_PATH "")
      endif()
    endif()
  endforeach()

  if(CLANG_COMPILER_HEADER_SEARCH_PATH STREQUAL "")
    message(FATAL_ERROR "Unable to copy Clang compiler headers from clang build dir.")
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
  COMPONENTS system
             program_options
             filesystem
             date_time
  REQUIRED)

# Qt ---------------------------------------------------------------------------

set(QT_MIN_VERSION "5.12.0")
set(QT_MIN_VERSION_HEX 0x051200)
find_package(
  Qt5 ${QT_MIN_VERSION}
  COMPONENTS Widgets
             PrintSupport
             Network
             Svg
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

# Setup
# ---------------------------------------------------------------------------

include(cmake/copy_qt_dll.cmake)

add_subdirectory(src/external)
add_subdirectory(src/lib)
add_subdirectory(src/lib_cxx)
add_subdirectory(src/lib_gui)
add_subdirectory(src/lib_java)
add_subdirectory(src/lib_python)
add_subdirectory(src/lib_utility)

# Lib Utility ------------------------------------------------------------------

add_library(${LIB_UTILITY_PROJECT_NAME} ${LIB_UTILITY_FILES})

create_source_groups(${LIB_UTILITY_FILES})

target_include_directories(${LIB_UTILITY_PROJECT_NAME} PUBLIC "${LIB_UTILITY_INCLUDE_PATHS}")

target_link_libraries(${LIB_UTILITY_PROJECT_NAME} PUBLIC Qt5::Core Boost::system sqlite::sqlite tinyxml::tinyxml)

if(UNIX AND NOT APPLE)
  find_package(Threads REQUIRED)
  target_link_libraries(${LIB_UTILITY_PROJECT_NAME} PUBLIC Threads::Threads)
endif()

if(WIN32)
  target_link_libraries(${LIB_UTILITY_PROJECT_NAME} PUBLIC Qt5::WinExtras bcrypt.lib)
endif()

set_project_warnings(${LIB_UTILITY_PROJECT_NAME})

# Lib --------------------------------------------------------------------------

add_library(${LIB_PROJECT_NAME} ${LIB_FILES} ${EXTERNAL_FILES} ${EXTERNAL_C_FILES})

create_source_groups(${LIB_FILES})
create_source_groups(${EXTERNAL_FILES})
create_source_groups(${EXTERNAL_C_FILES})

set_property(TARGET ${LIB_PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES)

target_include_directories(
  ${LIB_PROJECT_NAME}
  PUBLIC "${LIB_INCLUDE_PATHS}"
         "${LIB_GUI_INCLUDE_PATHS}"
         "${LIB_UTILITY_INCLUDE_PATHS}"
         "${LIB_CXX_INCLUDE_PATHS}"
         "${LIB_JAVA_INCLUDE_PATHS}"
         "${CMAKE_BINARY_DIR}/src/lib")

target_include_directories(${LIB_PROJECT_NAME} SYSTEM PUBLIC "${EXTERNAL_INCLUDE_PATHS}" "${EXTERNAL_C_INCLUDE_PATHS}")

target_link_libraries(
  ${LIB_PROJECT_NAME}
  PUBLIC ${LIB_UTILITY_PROJECT_NAME}
         ${LIB_GUI_PROJECT_NAME}
         Boost::program_options
         Boost::filesystem
         Boost::date_time)

# configure language package defines
configure_file("${CMAKE_SOURCE_DIR}/cmake/language_packages.h.in" "${CMAKE_BINARY_DIR}/src/lib/language_packages.h")

set_project_warnings(${LIB_PROJECT_NAME})

# Lib Cxx ----------------------------------------------------------------------

if(BUILD_CXX_LANGUAGE_PACKAGE)
  add_library(${LIB_CXX_PROJECT_NAME} ${LIB_CXX_FILES})

  create_source_groups(${LIB_CXX_FILES})

  set_property(
    TARGET ${LIB_CXX_PROJECT_NAME}
    PROPERTY INCLUDE_DIRECTORIES
             "${LIB_CXX_INCLUDE_PATHS}"
             "${LIB_UTILITY_INCLUDE_PATHS}"
             "${LIB_INCLUDE_PATHS}"
             "${CMAKE_BINARY_DIR}/src/lib")

  target_include_directories(
    ${LIB_CXX_PROJECT_NAME} SYSTEM
    PUBLIC ${LLVM_INCLUDE_DIRS}
           ${CLANG_INCLUDE_DIRS}
           ${Boost_INCLUDE_DIRS}
           "${EXTERNAL_INCLUDE_PATHS}"
           "${EXTERNAL_C_INCLUDE_PATHS}")

  link_directories(${LLVM_LIBRARY_DIRS} ${CLANG_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

  set_target_properties(${LIB_CXX_PROJECT_NAME} PROPERTIES CXX_STANDARD 14)

  if(LLVM_LINK_LLVM_DYLIB)
    set(REQ_LLVM_LIBS LLVM)
  else()
    llvm_map_components_to_libnames(
      REQ_LLVM_LIBS
      support
      core
      libdriver
      passes
      option)
    foreach(LLVM_TARGET ${LLVM_TARGETS_TO_BUILD})
      get_property(lib_deps GLOBAL PROPERTY "LLVMBUILD_LIB_DEPS_LLVM${LLVM_TARGET}CodeGen")
      list(APPEND REQ_LLVM_LIBS "LLVM${LLVM_TARGET}CodeGen")
      list(APPEND REQ_LLVM_LIBS "${lib_deps}")
      get_property(lib_deps GLOBAL PROPERTY "LLVMBUILD_LIB_DEPS_LLVM${LLVM_TARGET}AsmParser")
      if(NOT
         "${lib_deps}"
         STREQUAL
         "")
        list(APPEND REQ_LLVM_LIBS "LLVM${LLVM_TARGET}AsmParser")
        list(APPEND REQ_LLVM_LIBS "${lib_deps}")
      endif()
    endforeach()
  endif()

  if(LLVM_LINK_LLVM_DYLIB) # Should be CLANG_LINK_CLANG_DYLIB in future LLVM
                           # release
    set(CLANG_LIBRARIES clang-cpp)
  else()
    set(CLANG_LIBRARIES
        clangASTMatchers
        clangFrontend
        clangSerialization
        clangDriver
        clangTooling
        clangParse
        clangSema
        clangStaticAnalyzerFrontend
        clangStaticAnalyzerCheckers
        clangStaticAnalyzerCore
        clangAnalysis
        clangRewriteFrontend
        clangEdit
        clangAST
        clangLex
        clangBasic)
  endif()

  target_link_libraries(
    ${LIB_CXX_PROJECT_NAME}
    ${LIB_UTILITY_PROJECT_NAME}
    ${CLANG_LIBRARIES}
    ${REQ_LLVM_LIBS})

  if(WIN32)
    target_compile_definitions(${LIB_CXX_PROJECT_NAME} PRIVATE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS) # Due to Clang
    target_link_libraries(${LIB_CXX_PROJECT_NAME} version)
  endif()
else()

  message(
    STATUS
      "Building the Cxx indexer will be skipped. You can enable building this target by setting 'BUILD_CXX_LANGUAGE_PACKAGE' to 'ON'."
  )

endif()

# Lib Java ---------------------------------------------------------------------

if(BUILD_JAVA_LANGUAGE_PACKAGE)

  find_package(JNI)

  add_library(${LIB_JAVA_PROJECT_NAME} ${LIB_JAVA_FILES})

  create_source_groups(${LIB_JAVA_FILES})

  set_property(
    TARGET ${LIB_JAVA_PROJECT_NAME}
    PROPERTY INCLUDE_DIRECTORIES
             "${LIB_JAVA_INCLUDE_PATHS}"
             "${LIB_UTILITY_INCLUDE_PATHS}"
             "${LIB_INCLUDE_PATHS}"
             "${LIB_GUI_INCLUDE_PATHS}"
             "${CMAKE_BINARY_DIR}/src/lib")

  target_include_directories(${LIB_JAVA_PROJECT_NAME} SYSTEM PUBLIC ${JNI_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

  link_directories(${Boost_LIBRARY_DIRS})

  target_link_libraries(${LIB_JAVA_PROJECT_NAME} ${LIB_UTILITY_PROJECT_NAME} ${LIB_PROJECT_NAME})

  add_custom_command(
    TARGET ${LIB_JAVA_PROJECT_NAME}
    PRE_BUILD
    COMMAND ${BASH} ${PROJECT_SOURCE_DIR}/script/update_java_indexer.sh
    COMMENT "updating java indexer jars")

else()

  message(
    STATUS
      "Building the Java indexer will be skipped. You can enable building this target by setting 'BUILD_JAVA_LANGUAGE_PACKAGE' to 'ON'."
  )

endif()

# Lib Python
# ---------------------------------------------------------------------

if(BUILD_PYTHON_LANGUAGE_PACKAGE)

  add_library(${LIB_PYTHON_PROJECT_NAME} ${LIB_PYTHON_FILES})

  create_source_groups(${LIB_PYTHON_FILES})

  set_property(
    TARGET ${LIB_PYTHON_PROJECT_NAME}
    PROPERTY INCLUDE_DIRECTORIES
             "${LIB_PYTHON_INCLUDE_PATHS}"
             "${LIB_UTILITY_INCLUDE_PATHS}"
             "${LIB_INCLUDE_PATHS}"
             "${CMAKE_BINARY_DIR}/src/lib")

  target_link_libraries(${LIB_PYTHON_PROJECT_NAME} ${LIB_UTILITY_PROJECT_NAME} ${LIB_PROJECT_NAME})

  add_custom_command(
    TARGET ${LIB_PYTHON_PROJECT_NAME}
    PRE_BUILD
    COMMAND ${BASH} ${PROJECT_SOURCE_DIR}/script/download_python_indexer.sh
    COMMENT "download python indexer")

else()

  message(
    STATUS
      "Building the Python indexer will be skipped. You can enable building this target by setting 'BUILD_PYTHON_LANGUAGE_PACKAGE' to 'ON'."
  )

endif()

# Lib Gui ----------------------------------------------------------------------

# target for running versionnumber script workaround for running customcommand
# (ninja dependency cycle)
add_custom_target(versionnumber ALL)

add_library(${LIB_GUI_PROJECT_NAME} ${LIB_GUI_FILES} ${CMAKE_BINARY_DIR}/src/lib_gui/productVersion.h)

target_link_libraries(
  ${LIB_GUI_PROJECT_NAME}
  PUBLIC ${LIB_UTILITY_PROJECT_NAME}
         ${LIB_PROJECT_NAME}
         Boost::program_options
         Boost::filesystem
         Boost::date_time
         Qt5::Widgets
         Qt5::Network
         Qt5::Svg)

if(WIN32)
  target_link_libraries(${LIB_GUI_PROJECT_NAME} PUBLIC Qt5::WinExtras)
endif()

# command for versioning script
add_custom_command(
  TARGET versionnumber
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -DBINARY_DIR=${CMAKE_BINARY_DIR} -P ${CMAKE_SOURCE_DIR}/cmake/version.cmake
  BYPRODUCTS ${CMAKE_BINARY_DIR}/src/lib_gui/productVersion.h DEPENDS ${LIB_GUI_PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "check/update version number")

add_dependencies(${LIB_GUI_PROJECT_NAME} versionnumber)

create_source_groups(${LIB_GUI_FILES})

set_property(
  TARGET ${LIB_GUI_PROJECT_NAME}
  PROPERTY INCLUDE_DIRECTORIES
           "${LIB_GUI_INCLUDE_PATHS}"
           "${LIB_UTILITY_INCLUDE_PATHS}"
           "${LIB_INCLUDE_PATHS}"
           "${CMAKE_BINARY_DIR}/src/lib_gui"
           "${CMAKE_BINARY_DIR}/src/lib"
           $<$<BOOL:${BUILD_CXX_LANGUAGE_PACKAGE}>:${LIB_CXX_INCLUDE_PATHS}>
           $<$<BOOL:${BUILD_JAVA_LANGUAGE_PACKAGE}>:${LIB_JAVA_INCLUDE_PATHS}>
           $<$<BOOL:${BUILD_PYTHON_LANGUAGE_PACKAGE}>:${LIB_PYTHON_INCLUDE_PATHS}>)

# include external header without warnings
target_include_directories(${LIB_GUI_PROJECT_NAME} SYSTEM PUBLIC "${EXTERNAL_INCLUDE_PATHS}"
                                                                 "${EXTERNAL_C_INCLUDE_PATHS}")

# configure platform specific include file
configure_file("${PROJECT_SOURCE_DIR}/src/lib_gui/platform_includes/includes.h.in"
               "${PROJECT_BINARY_DIR}/src/lib_gui/includes.h")

# configure the versioning file
configure_file(${CMAKE_SOURCE_DIR}/cmake/version.txt.in ${CMAKE_BINARY_DIR}/version.txt)

configure_file(${CMAKE_SOURCE_DIR}/cmake/productVersion.h.in ${CMAKE_BINARY_DIR}/src/lib_gui/productVersion.h)

set_property(SOURCE ${CMAKE_BINARY_DIR}/src/lib_gui/productVersion.h PROPERTY SKIP_AUTOMOC ON)

set_target_properties(${LIB_GUI_PROJECT_NAME} PROPERTIES AUTOMOC ON INCLUDE_CURRENT_DIR ON)
# applications --------------------------------------------------------------
add_subdirectory(src/indexer)

add_subdirectory(src/app)
# macOS Bundle --------------------------------------------------------------
if(APPLE)
  set(MACOS_BUNDLE_NAME ${PROJECT_NAME})
  set(MACOS_BUNDLE_VERSION ${VERSION_STRING})
  set(MACOS_BINARY_NAME Sourcetrail)
  set(MACOS_INDEXER_BINARY_NAME Sourcetrail_indexer)

  get_property(
    QT_CORE_PATH
    TARGET ${Qt5Core_LIBRARIES}
    PROPERTY LOCATION)
  get_filename_component(QT_CORE_PATH ${QT_CORE_PATH} REALPATH)

  get_property(
    QT_GUI_PATH
    TARGET ${Qt5Gui_LIBRARIES}
    PROPERTY LOCATION)
  get_filename_component(QT_GUI_PATH ${QT_GUI_PATH} REALPATH)

  get_property(
    QT_WIDGETS_PATH
    TARGET ${Qt5Widgets_LIBRARIES}
    PROPERTY LOCATION)
  get_filename_component(QT_WIDGETS_PATH ${QT_WIDGETS_PATH} REALPATH)

  get_property(
    QT_PRINT_PATH
    TARGET ${Qt5PrintSupport_LIBRARIES}
    PROPERTY LOCATION)
  get_filename_component(QT_PRINT_PATH ${QT_PRINT_PATH} REALPATH)

  get_property(
    QT_NETWORK_PATH
    TARGET ${Qt5Network_LIBRARIES}
    PROPERTY LOCATION)
  get_filename_component(QT_NETWORK_PATH ${QT_NETWORK_PATH} REALPATH)

  get_property(
    QT_SVG_PATH
    TARGET ${Qt5Svg_LIBRARIES}
    PROPERTY LOCATION)
  get_filename_component(QT_SVG_PATH ${QT_SVG_PATH} REALPATH)

  list(
    APPEND
    MACOS_QT_FRAMEWORKS
    ${QT_CORE_PATH}
    ${QT_GUI_PATH}
    ${QT_WIDGETS_PATH}
    ${QT_PRINT_PATH}
    ${QT_NETWORK_PATH}
    ${QT_SVG_PATH})
  string(
    REPLACE ";"
            " "
            MACOS_QT_FRAMEWORKS
            "${MACOS_QT_FRAMEWORKS}")

  set(MACOS_BOOST_DIR "${Boost_INCLUDE_DIR}")
  string(
    REGEX
    REPLACE "/lib/cmake/clang"
            ""
            MACOS_CLANG_DIR
            "${Clang_DIR}")
  string(
    REGEX
    REPLACE "/lib/cmake/Qt5"
            ""
            MACOS_QT_DIR
            "${Qt5_DIR}")

  configure_file(${PROJECT_SOURCE_DIR}/setup/macOS/bundle_install.sh.in
                 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bundle_install.sh @ONLY)

  configure_file(${PROJECT_SOURCE_DIR}/setup/macOS/bundle_info.plist.in
                 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bundle_info.plist @ONLY)
endif()
# Test ----------------------------------------------------------------------
if(BUILD_FUNC OR BUILD_TEST OR BUILD_BENCHMARK)
  add_library(test_main OBJECT src/test/test_main.cpp)

  target_link_libraries(test_main PUBLIC Sourcetrail_lib)

  target_include_directories(test_main SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/external/catch/)

  if(BUILD_FUNC OR BUILD_TEST)
    enable_testing()

    if(BUILD_TEST)
      add_subdirectory(src/test)
    endif()

    if(BUILD_FUNC)
      add_subdirectory(src/functionality)
    endif()
  endif()

  # Test ----------------------------------------------------------------------
  if(BUILD_BENCHMARK)
    target_compile_definitions(test_main PRIVATE CATCH_CONFIG_ENABLE_BENCHMARKING)

    add_subdirectory(src/benchmark)
  endif()
endif()
# Data ----------------------------------------------------------------------
execute_process(COMMAND "${CMAKE_COMMAND}" "-E" "make_directory" "${CMAKE_BINARY_DIR}/app")
execute_process(
  COMMAND "${CMAKE_COMMAND}" "-E" "create_symlink" "${CMAKE_SOURCE_DIR}/bin/app/data" "${CMAKE_BINARY_DIR}/app/data"
  COMMAND "${CMAKE_COMMAND}" "-E" "create_symlink" "${CMAKE_SOURCE_DIR}/bin/app/user" "${CMAKE_BINARY_DIR}/app/user")
