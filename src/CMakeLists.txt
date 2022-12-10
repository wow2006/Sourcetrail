# ${CMAKE_SOURCE_DIR}/src/CMakeLists.txt
set(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_LIBS ON CACHE BOOL "Set to ON to force the use of the static libraries.")
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.67 COMPONENTS system program_options filesystem date_time REQUIRED)

find_package(Qt5 5.12 COMPONENTS Widgets PrintSupport Network Svg REQUIRED)

add_subdirectory(external)
add_subdirectory(lib_utility)
#add_subdirectory(lib)
#add_subdirectory(app)

if(BUILD_UNIT_TESTS OR BUILD_FUNC_TESTS)
    add_subdirectory(test)
endif()