# ${CMAKE_SOURCE_DIR}/src/external/tinyxml/CMakeLists.txt
add_library(tinyxml)

target_sources(
  tinyxml
  PRIVATE tinystr.cpp
          tinyxml.cpp
          tinyxmlerror.cpp
          tinyxmlparser.cpp)

target_include_directories(tinyxml SYSTEM PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_compile_options(tinyxml PRIVATE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-w>
                                       $<$<CXX_COMPILER_ID:MSVC>:/WX>)

add_library(tinyxml::tinyxml ALIAS tinyxml)
