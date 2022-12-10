# ${CMAKE_SOURCE_DIR}/src/external/catch/CMakeLists.txt
add_library(
    catch
    INTERFACE
)

target_include_directories(
    catch
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

add_library(
    catch::catch
    ALIAS
    catch
)