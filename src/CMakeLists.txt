# ${CMAKE_SOURCE_DIR}/src/CMakeLists.txt
add_subdirectory(external)

# ==========================================
# TESTING
# ==========================================

add_library(Sourcetrail_lib_logger)

add_library(Sourcetrail::lib::logger ALIAS Sourcetrail_lib_logger)

target_sources(Sourcetrail_lib_logger PRIVATE lib/utility/logging/Logger.cpp)

target_include_directories(Sourcetrail_lib_logger PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib/utility/logging/)

target_link_libraries(Sourcetrail_lib_logger PUBLIC fmt::fmt)

target_precompile_headers(Sourcetrail_lib_logger PUBLIC lib/precompiled.hpp)

set_project_warnings(Sourcetrail_lib_logger)

# ==========================================

add_library(Sourcetrail_lib_utility_file)

add_library(Sourcetrail::lib::utility::file ALIAS Sourcetrail_lib_utility_file)

target_sources(
  Sourcetrail_lib_utility_file
  PRIVATE lib/utility/file/FileInfo.cpp
          lib/utility/file/FileManager.cpp
          lib/utility/file/FilePath.cpp
          lib/utility/file/FilePathFilter.cpp
          lib/utility/file/FileRegister.cpp
          lib/utility/file/FileSystem.cpp
          lib/utility/file/FileTree.cpp
          lib/utility/file/utilityFile.cpp)

target_link_libraries(Sourcetrail_lib_utility_file PRIVATE fmt::fmt Sourcetrail::lib_utility Sourcetrail::lib::logger)

target_include_directories(
  Sourcetrail_lib_utility_file
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/utility
          ${CMAKE_CURRENT_SOURCE_DIR}/lib/utility/file/
)

target_precompile_headers(Sourcetrail_lib_utility_file PUBLIC lib/precompiled.hpp)

set_project_warnings(Sourcetrail_lib_utility_file)

# ==========================================

if(BUILD_CXX_LANGUAGE_PACKAGE)
  add_subdirectory(lib_cxx)
endif()

add_subdirectory(lib_utility)
add_subdirectory(lib)
add_subdirectory(lib_gui)

if(BUILD_TEST
   OR BUILD_FUNC
   OR BUILD_BENCHMARK)
  add_library(test_main OBJECT test/test_main.cpp)
  target_link_libraries(test_main PUBLIC Sourcetrail::lib_gui catch::catch)
endif()

if(BUILD_TEST)
  add_subdirectory(test)
endif()

add_subdirectory(indexer)
add_subdirectory(app)
