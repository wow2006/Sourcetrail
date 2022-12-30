# ${CMAKE_SOURCE_DIR}/src/indexer/CMakeLists.txt
project(Sourcetrail_indexer CXX)

add_executable(Sourcetrail_indexer main.cpp)

set_target_properties(Sourcetrail_indexer PROPERTIES OUTPUT_NAME
                                                     sourcetrail_indexer)

if(WIN32)
  # hide the console when running a release build.
  set_target_properties(
    Sourcetrail_indexer
    PROPERTIES COMPILE_DEFINITIONS                "_CONSOLE"
               LINK_FLAGS_RELEASE                 "/ENTRY:\"mainCRTStartup\" /SUBSYSTEM:WINDOWS /DEBUG"
               LINK_FLAGS_DEBUG                   "/SUBSYSTEM:CONSOLE /DEBUG:FASTLINK"
               LINK_FLAGS_RELWITHDEBINFO          "/SUBSYSTEM:CONSOLE"
               LINK_FLAGS_MINSIZEREL              "/SUBSYSTEM:WINDOWS"
               # generate pdb for release build
               # The /Zi option produces a separate PDB file
               CXX_FLAGS_RELEASE                  "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
endif()

target_link_libraries(
  Sourcetrail_indexer
  PRIVATE Sourcetrail_lib
          $<$<BOOL:${BUILD_CXX_LANGUAGE_PACKAGE}>:${LIB_CXX_PROJECT_NAME}>
          $<$<BOOL:${BUILD_JAVA_LANGUAGE_PACKAGE}>:${LIB_JAVA_PROJECT_NAME}>
          $<$<BOOL:${BUILD_PYTHON_LANGUAGE_PACKAGE}>:${LIB_PYTHON_PROJECT_NAME}>)

target_include_directories(
  Sourcetrail_indexer
  SYSTEM PRIVATE
    "${CMAKE_BINARY_DIR}/src/lib_gui")

set_target_properties(Sourcetrail_indexer PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                     "${CMAKE_BINARY_DIR}/app/")

set_project_warnings(Sourcetrail_indexer)

if(APPLE)
  find_library(CORE_FOUNDATION CoreFoundation)
  target_link_libraries(Sourcetrail_indexer PRIVATE ${CORE_FOUNDATION})
endif()
