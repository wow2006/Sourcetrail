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

  set(
    test_files
    FilePathTestSuite
    LogManagerTestSuite
    LogMessageTestSuite
    MessageQueueTestSuite
    ScopedFunctorTestSuite
    TaskGroupParallelTestSuite
    TaskManagerTestSuite
    TaskRunnerTestSuite
    TaskSchedulerTestSuite
    TextAccessTestSuite
    TextCodecTestSuite
    TimeStampTestSuite
    UtilityStringTestSuite
  )

  foreach(test_file IN LISTS test_files)
    add_executable(${test_file} ${test_file}.cpp $<TARGET_OBJECTS:test_main>)

    target_link_libraries(
      ${test_file}
      PRIVATE catch::catch
              Sourcetrail::lib
              Sourcetrail::lib_utility
              $<$<BOOL:${ENABLE_ADDRESS_ASAN}>:Sanaitizer::Address>
              $<$<BOOL:${ENABLE_MEMORY_ASAN}>:Sanaitizer::Memory>)

    set_target_properties(${test_file} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

    add_test(
      NAME ${test_file}
      COMMAND ${test_file}
      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
  endforeach()

  add_dependencies(TextAccessTestSuite LinkTestingData)
endif()

if(BUILD_FUNC_TESTS)
  add_subdirectory(functionality)
endif()
