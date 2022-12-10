if(ENABLE_DOXYGEN)
  set(DOXYGEN_CALLER_GRAPH YES)
  set(DOXYGEN_CALL_GRAPH YES)
  set(DOXYGEN_EXTRACT_ALL YES)
  find_package(Doxygen REQUIRED dot)
  doxygen_add_docs(
    doxygen-docs
    ${CMAKE_SOURCE_DIR}/src/lib/
    ${CMAKE_SOURCE_DIR}/src/lib_utility/
    ${CMAKE_SOURCE_DIR}/src/lib_gui)
endif()
