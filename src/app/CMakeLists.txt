# ${CMAKE_SOURCE_DIR}/src/app/CMakeLists.txt
add_subdirectory(indexer)
add_subdirectory(gui)
if(BUILD_EXPORT_UML)
  add_subdirectory(export_UML)
endif()

