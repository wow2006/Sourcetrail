# add_files(
#   TEST

#   helper/TestFileRegister.cpp
#   helper/TestFileRegister.h
#   helper/TestStorage.h

#   test_main.cpp

#   ConfigManagerTestSuite.cpp
#   CxxIncludeProcessingTestSuite.cpp
#   CxxParserTestSuite.cpp
#   CxxTypeNameTestSuite.cpp
#   FileManagerTestSuite.cpp
#   FilePathFilterTestSuite.cpp
#   FilePathTestSuite.cpp
#   FileSystemTestSuite.cpp
#   GraphTestSuite.cpp
#   HierarchyCacheTestSuite.cpp
#   JavaIndexSampleProjectsTestSuite.cpp
#   JavaParserTestSuite.cpp
#   LogManagerTestSuite.cpp
#   LowMemoryStringMapTestSuite.cpp
#   MatrixBaseTestSuite.cpp
#   MatrixDynamicBaseTestSuite.cpp
#   MessageQueueTestSuite.cpp
#   NetworkProtocolHelperTestSuite.cpp
#   PythonIndexerTestSuite.cpp
#   RefreshInfoGeneratorTestSuite.cpp
#   SearchIndexTestSuite.cpp
#   SettingsMigratorTestSuite.cpp
#   SettingsTestSuite.cpp
#   SharedMemoryTestSuite.cpp
#   SourceGroupTestSuite.cpp
#   SourceLocationCollectionTestSuite.cpp
#   SqliteBookmarkStorageTestSuite.cpp
#   SqliteIndexStorageTestSuite.cpp
#   StorageTestSuite.cpp
#   TaskSchedulerTestSuite.cpp
#   TextAccessTestSuite.cpp
#   UtilityGradleTestSuite.cpp
#   UtilityMavenTestSuite.cpp
#   UtilityStringTestSuite.cpp
#   UtilityTestSuite.cpp
#   Vector2TestSuite.cpp
# )

if(BUILD_UNIT_TESTS)
  add_custom_target(
    CopyDataToTestsDir
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/tests/data/"
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/bin/app/data/fallback/ApplicationSettings.xml
            ${CMAKE_BINARY_DIR}/tests/data/ApplicationSettings.xml)

  add_library(test_main OBJECT test_main.cpp)

  target_link_libraries(test_main PUBLIC Sourcetrail_lib)

  target_include_directories(test_main SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/external/catch/)

  if(FALSE)
    add_executable(CommandlineTestSuite CommandlineTestSuite.cpp $<TARGET_OBJECTS:test_main>)

    target_link_libraries(
      CommandlineTestSuite
      PRIVATE Sourcetrail_lib
              Sourcetrail_lib_utility
              $<$<BOOL:${ENABLE_ADDRESS_ASAN}>:Sanaitizer::Address>
              $<$<BOOL:${ENABLE_MEMORY_ASAN}>:Sanaitizer::Memory>)

    set_target_properties(CommandlineTestSuite PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

    add_dependencies(CommandlineTestSuite CopyDataToTestsDir)

    add_test(
      NAME CommandlineTestSuite
      COMMAND CommandlineTestSuite
      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
  endif()

  add_executable(UtilityStringTestSuite UtilityStringTestSuite.cpp $<TARGET_OBJECTS:test_main>)

  target_link_libraries(
    UtilityStringTestSuite
    PRIVATE catch::catch
            Sourcetrail::lib_utility
            $<$<BOOL:${ENABLE_ADDRESS_ASAN}>:Sanaitizer::Address>
            $<$<BOOL:${ENABLE_MEMORY_ASAN}>:Sanaitizer::Memory>)

  set_target_properties(UtilityStringTestSuite PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

  add_test(
    NAME UtilityStringTestSuite
    COMMAND UtilityStringTestSuite
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
endif()

if(BUILD_FUNC_TESTS)
  add_subdirectory(functionality)
endif()
