# ${CMAKE_SOURCE_DIR}/src/external/sqlite/CMakeLists.txt
project(sqlite C CXX)
add_library(sqlite)

target_sources(sqlite PRIVATE CppSQLite3.cpp sqlite3.c)

target_include_directories(sqlite SYSTEM PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_compile_options(
  sqlite
  PRIVATE $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-w>
          $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-w>
          $<$<C_COMPILER_ID:MSVC>:/WX>
          $<$<CXX_COMPILER_ID:MSVC>:/WX>)

add_library(sqlite::sqlite ALIAS sqlite)
