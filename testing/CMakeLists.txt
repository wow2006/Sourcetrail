# ${CMAKE_SOURCE_DIR}/testing/CMakeLists.txt
set(helloWorld_PATH "${CMAKE_CURRENT_LIST_DIR}/helloWorld.tar.gz")

if(NOT EXISTS ${helloWorld_PATH})
    file(
        DOWNLOAD "https://docs.google.com/uc?export=download&id=1Q6ApDnDrYn5RMPtldd49_FVC9UujTZPn"
                  ${helloWorld_PATH}
                  SHOW_PROGRESS
                  EXPECTED_MD5 eeb2359d2533ebf945f3fc922a701381
    )
endif()

add_custom_target(
    ExtractHelloWorld
    COMMAND ${CMAKE_COMMAND} -E tar xf ${helloWorld_PATH}
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/data/"
    DEPENDS ${helloWorld_PATH}
)
