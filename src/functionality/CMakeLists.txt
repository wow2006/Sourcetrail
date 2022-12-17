# ${CMAKE_SOURCE_DIR}/src/functionality/CMakeLists.txt
find_package(Python3 COMPONENTS Interpreter Development)

add_test(
	NAME IndexerFuncTest
	COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/indexerFuncTest.py
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app/
)