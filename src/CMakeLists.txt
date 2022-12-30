# ${CMAKE_SOURCE_DIR}/src/CMakeLists.txt
add_subdirectory(external)
add_subdirectory(lib_utility)
add_subdirectory(lib)
add_subdirectory(lib_gui)

if(BUILD_TEST OR BUILD_FUNC OR BUILD_BENCHMARK)
  add_library(test_main OBJECT test/test_main.cpp)
  target_link_libraries(test_main PUBLIC Sourcetrail::lib_gui catch::catch)
endif()

if(BUILD_TEST)
  add_subdirectory(test)
endif()

add_subdirectory(indexer)
add_subdirectory(app)
