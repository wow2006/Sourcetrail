add_files(
  TEST

  helper/TestFileRegister.cpp
  helper/TestFileRegister.h
  helper/TestStorage.h

  test_main.cpp

  CommandlineTestSuite.cpp
  ConfigManagerTestSuite.cpp
  CxxIncludeProcessingTestSuite.cpp
  CxxParserTestSuite.cpp
  CxxTypeNameTestSuite.cpp
  FileManagerTestSuite.cpp
  FilePathFilterTestSuite.cpp
  FilePathTestSuite.cpp
  GraphTestSuite.cpp
  HierarchyCacheTestSuite.cpp
  JavaIndexSampleProjectsTestSuite.cpp
  JavaParserTestSuite.cpp
  LogManagerTestSuite.cpp
  LowMemoryStringMapTestSuite.cpp
  MatrixBaseTestSuite.cpp
  MatrixDynamicBaseTestSuite.cpp
  MessageQueueTestSuite.cpp
  NetworkProtocolHelperTestSuite.cpp
  PythonIndexerTestSuite.cpp
  SearchIndexTestSuite.cpp
  SettingsMigratorTestSuite.cpp
  SettingsTestSuite.cpp
  SourceLocationCollectionTestSuite.cpp
  TaskSchedulerTestSuite.cpp
  TextAccessTestSuite.cpp
  UtilityGradleTestSuite.cpp
  UtilityMavenTestSuite.cpp
  UtilityStringTestSuite.cpp
  UtilityTestSuite.cpp
  Vector2TestSuite.cpp

  SharedMemoryTestSuite.cpp
  SourceGroupTestSuite.cpp
  FileSystemTestSuite.cpp
)

add_files(
  FUNC

  helper/TestFileRegister.cpp
  helper/TestFileRegister.h
  helper/TestStorage.h

  test_main.cpp

  RefreshInfoGeneratorTestSuite.cpp
  SqliteBookmarkStorageTestSuite.cpp
  SqliteIndexStorageTestSuite.cpp
  StorageTestSuite.cpp
)

