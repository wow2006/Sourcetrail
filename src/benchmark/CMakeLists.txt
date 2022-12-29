# ${CMAKE_SOURCE_DIR}/src/benchmark/CMakeLists.txt

# All the remaining benchmark cases
set(benchmark_files UtilityStringBenchmark)

foreach(benchmark_file IN LISTS benchmark_files)
  add_executable(${benchmark_file} ${benchmark_file}.cpp $<TARGET_OBJECTS:test_main>)

  target_link_libraries(
    ${benchmark_file}
    PRIVATE test_utilities
            $<$<BOOL:${BUILD_CXX_LANGUAGE_PACKAGE}>:${LIB_CXX_PROJECT_NAME}>
            $<$<BOOL:${ENABLE_ADDRESS_ASAN}>:Sanaitizer::Address>
            $<$<BOOL:${ENABLE_MEMORY_ASAN}>:Sanaitizer::Memory>)

  set_target_properties(${benchmark_file} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/benchmark")

  target_compile_definitions(${benchmark_file} PRIVATE CATCH_CONFIG_ENABLE_BENCHMARKING)

  if(WIN32)
    set_property(TARGET ${benchmark_file} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/benchmark")
  endif()
endforeach()
