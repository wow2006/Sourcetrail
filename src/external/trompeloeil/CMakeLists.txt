# ${CMAKE_SOURCE_DIR}/src/external/trompeloeil/CMakeLists.txt
add_library(
    trompeloeil
    INTERFACE
)

target_include_directories(
    trompeloeil
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

add_library(
    trompeloeil::trompeloeil
    ALIAS
    trompeloeil
)