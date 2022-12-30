# ${CMAKE_SOURCE_DIR}/src/app/CMakeLists.txt
if(WIN32)
  file(
    WRITE ${CMAKE_BINARY_DIR}/Sourcetrail.rc
    "// Icon with lowest ID value placed first to ensure application icon\n"
    "// remains consistent on all systems.\n"
    "IDI_ICON1               ICON                    \"${CMAKE_BINARY_DIR}/Sourcetrail.ico\"\n"
  )

  add_executable(Sourcetrail main.cpp ${CMAKE_BINARY_DIR}/Sourcetrail.rc)

  # also show the console when running a release build.
  set_target_properties(
    Sourcetrail
    PROPERTIES COMPILE_DEFINITIONS_DEBUG          "_CONSOLE"
               COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE"
               LINK_FLAGS_DEBUG                   "/SUBSYSTEM:CONSOLE /DEBUG:FASTLINK"
               LINK_FLAGS_RELWITHDEBINFO          "/SUBSYSTEM:CONSOLE"
               LINK_FLAGS_RELEASE                 "/ENTRY:\"mainCRTStartup\" /SUBSYSTEM:CONSOLE /DEBUG"
               LINK_FLAGS_MINSIZEREL              "/SUBSYSTEM:CONSOLE"
               # generate pdb for release build
               CXX_FLAGS_RELEASE                  "${CMAKE_CXX_FLAGS_RELEASE} /Zi"
               VS_DEBUGGER_WORKING_DIRECTORY      "${CMAKE_SOURCE_DIR}/bin/app")

  string(REGEX REPLACE "/" "\\\\" BACKSLASHED_CMAKE_BINARY_DIR
                       ${CMAKE_BINARY_DIR})
  string(REGEX REPLACE "/" "\\\\" BACKSLASHED_CMAKE_SOURCE_DIR
                       ${CMAKE_SOURCE_DIR})
else()
  add_executable(Sourcetrail main.cpp)
endif()

create_source_groups(Sourcetrail)

target_link_libraries(
  Sourcetrail
  PRIVATE
  Sourcetrail_lib
  Sourcetrail_lib_gui
  $<$<BOOL:${BUILD_CXX_LANGUAGE_PACKAGE}>:${LIB_CXX_PROJECT_NAME}>
  $<$<BOOL:${BUILD_JAVA_LANGUAGE_PACKAGE}>:${LIB_JAVA_PROJECT_NAME}>
  $<$<BOOL:${BUILD_PYTHON_LANGUAGE_PACKAGE}>:${LIB_PYTHON_PROJECT_NAME}>
  Qt5::Widgets
  Qt5::Network)

target_include_directories(
  Sourcetrail
  SYSTEM PRIVATE
    "${CMAKE_BINARY_DIR}/src/lib_gui")

set_target_properties(Sourcetrail PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                             "${CMAKE_BINARY_DIR}/app/")

# add platform specific libraries
if(APPLE)
  find_library(CORE_FOUNDATION CoreFoundation)
  target_link_libraries(Sourcetrail PRIVATE ${CORE_FOUNDATION})
endif()

add_dependencies(Sourcetrail Sourcetrail_indexer)

set_project_warnings(Sourcetrail)
