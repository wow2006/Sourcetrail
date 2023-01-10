# ${CMAKE_SOURCE_DIR}/src/test/CMakeLists.txt

add_custom_target(CreateTestDataSymLink
                  COMMAND "${CMAKE_COMMAND}" "-E" "make_directory" "${CMAKE_BINARY_DIR}/test" &&
                          "${CMAKE_COMMAND}" "-E" "create_symlink" "${CMAKE_SOURCE_DIR}/bin/test/data" "${CMAKE_BINARY_DIR}/test/data"
                  COMMENT "Create a symlink for test data")

# TestFileRegister
add_library(test_utilities helper/TestFileRegister.cpp)

target_include_directories(test_utilities
                           PUBLIC ${CMAKE_CURRENT_LIST_DIR}/helper/)

target_link_libraries(test_utilities PUBLIC catch::catch Sourcetrail::lib
                                            Sourcetrail::lib_utility)

# All the remaining test cases
set(test_files
    CommandlineTestSuite
    ConfigManagerTestSuite
    CxxIncludeProcessingTestSuite
    CxxParserTestSuite
    CxxTypeNameTestSuite
    FileManagerTestSuite
    FilePathFilterTestSuite
    FilePathTestSuite
    FileSystemTestSuite
    GraphTestSuite
    HierarchyCacheTestSuite
    JavaIndexSampleProjectsTestSuite
    JavaParserTestSuite
    LogManagerTestSuite
    LoggerTestSuite
    LowMemoryStringMapTestSuite
    MatrixBaseTestSuite
    MatrixDynamicBaseTestSuite
    MessageQueueTestSuite
    NetworkProtocolHelperTestSuite
    PythonIndexerTestSuite
    RefreshInfoGeneratorTestSuite
    SearchIndexTestSuite
    SettingsMigratorTestSuite
    SettingsTestSuite
    SharedMemoryTestSuite
    SourceGroupTestSuite
    SourceLocationCollectionTestSuite
    SqliteBookmarkStorageTestSuite
    SqliteIndexStorageTestSuite
    StatusTestSuite
    StorageTestSuite
    TaskSchedulerTestSuite
    TextAccessTestSuite
    TimeStampTestSuite
    UnorderedCacheTestSuite
    UtilityGradleTestSuite
    UtilityMavenTestSuite
    UtilityStringTestSuite
    UtilityTestSuite
    UtilityXmlTestSuite
    UtilityFileTestSuite
    Vector2TestSuite
    VersionTestSuite)

foreach(test_file IN LISTS test_files)
  add_executable(${test_file} ${test_file}.cpp $<TARGET_OBJECTS:test_main>)

  target_link_libraries(
    ${test_file}
    PRIVATE test_utilities
            Sourcetrail::lib
            Sourcetrail::lib_gui
            $<$<BOOL:${BUILD_CXX_LANGUAGE_PACKAGE}>:${LIB_CXX_PROJECT_NAME}>
            $<$<BOOL:${ENABLE_ADDRESS_ASAN}>:Sanaitizer::Address>
            $<$<BOOL:${ENABLE_MEMORY_ASAN}>:Sanaitizer::Memory>)

  set_target_properties(${test_file} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                "${CMAKE_BINARY_DIR}/test")

  add_test(
    NAME ${test_file}
    COMMAND ${test_file}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test)

  add_dependencies(${test_file} CreateTestDataSymLink)

  if(WIN32)
    set_property(TARGET ${test_file} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
                                              "${CMAKE_SOURCE_DIR}/bin/test")
  endif()
endforeach()
