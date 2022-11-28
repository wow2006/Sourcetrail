# add_files(
# 	TEST

# 	helper/TestFileRegister.cpp
# 	helper/TestFileRegister.h
# 	helper/TestStorage.h

# 	test_main.cpp

# 	ConfigManagerTestSuite.cpp
# 	CxxIncludeProcessingTestSuite.cpp
# 	CxxParserTestSuite.cpp
# 	CxxTypeNameTestSuite.cpp
# 	FileManagerTestSuite.cpp
# 	FilePathFilterTestSuite.cpp
# 	FilePathTestSuite.cpp
# 	FileSystemTestSuite.cpp
# 	GraphTestSuite.cpp
# 	HierarchyCacheTestSuite.cpp
# 	JavaIndexSampleProjectsTestSuite.cpp
# 	JavaParserTestSuite.cpp
# 	LogManagerTestSuite.cpp
# 	LowMemoryStringMapTestSuite.cpp
# 	MatrixBaseTestSuite.cpp
# 	MatrixDynamicBaseTestSuite.cpp
# 	MessageQueueTestSuite.cpp
# 	NetworkProtocolHelperTestSuite.cpp
# 	PythonIndexerTestSuite.cpp
# 	RefreshInfoGeneratorTestSuite.cpp
# 	SearchIndexTestSuite.cpp
# 	SettingsMigratorTestSuite.cpp
# 	SettingsTestSuite.cpp
# 	SharedMemoryTestSuite.cpp
# 	SourceGroupTestSuite.cpp
# 	SourceLocationCollectionTestSuite.cpp
# 	SqliteBookmarkStorageTestSuite.cpp
# 	SqliteIndexStorageTestSuite.cpp
# 	StorageTestSuite.cpp
# 	TaskSchedulerTestSuite.cpp
# 	TextAccessTestSuite.cpp
# 	UtilityGradleTestSuite.cpp
# 	UtilityMavenTestSuite.cpp
# 	UtilityStringTestSuite.cpp
# 	UtilityTestSuite.cpp
# 	Vector2TestSuite.cpp
# )

add_library(
	test_main
	OBJECT
	test_main.cpp
)

target_link_libraries(
	test_main
	PUBLIC
	Sourcetrail_lib
)

target_include_directories(
	test_main
	SYSTEM PUBLIC
	${CMAKE_SOURCE_DIR}/src/external/catch/
)

add_executable(
	CommandlineTestSuite
	CommandlineTestSuite.cpp
	$<TARGET_OBJECTS:test_main>
)

target_link_libraries(
	CommandlineTestSuite
	PRIVATE
	Sourcetrail_lib
	Sourcetrail_lib_utility
)

add_test(
	CommandlineTestSuite
	CommandlineTestSuite
)
