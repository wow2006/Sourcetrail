# ${CMAKE_SOURCE_DIR}/src/lib_utility/CMakeLists.txt
add_library(Sourcetrail_lib_utility)

add_library(Sourcetrail::lib_utility ALIAS Sourcetrail_lib_utility)

target_sources(Sourcetrail_lib_utility PRIVATE utility/TextCodec.cpp
                                               utility/utilityString.cpp)

target_include_directories(Sourcetrail_lib_utility
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/utility)

target_link_libraries(Sourcetrail_lib_utility PRIVATE Qt5::Widgets Qt5::Network Boost::system)

set_project_warnings(Sourcetrail_lib_utility)

if(UNIX AND NOT APPLE)
  find_package(Threads REQUIRED)
  target_link_libraries(Sourcetrail_lib_utility PRIVATE ${CMAKE_DL_LIBS}
                                                        Threads::Threads)
endif()