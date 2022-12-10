# ${CMAKE_SOURCE_DIR}/src/lib/CMakeLists.txt
add_library(
  Sourcetrail_lib_utility

  utility/TextCodec.cpp
  utility/utilityString.cpp
)

target_include_directories(
  Sourcetrail_lib_utility
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/utility
)

target_link_libraries(
  Sourcetrail_lib_utility
  PRIVATE
  Qt5::Core
)

set_project_warnings(Sourcetrail_lib_utility)

add_library(
  Sourcetrail::lib_utility
  ALIAS
  Sourcetrail_lib_utility
)
