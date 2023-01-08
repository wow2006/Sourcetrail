#pragma once

#include "BaseInterprocessDataManager.h"
#include "FilePath.h"

class InterprocessIndexingStatusManager : public BaseInterprocessDataManager {
public:
  InterprocessIndexingStatusManager(const std::string& instanceUuid, Id processId, bool isOwner);
  ~InterprocessIndexingStatusManager() override;

  void startIndexingSourceFile(const FilePath& filePath);
  void finishIndexingSourceFile();

  void setIndexingInterrupted(bool interrupted);
  bool getIndexingInterrupted();

  Id getNextFinishedProcessId();

  std::vector<FilePath> getCurrentlyIndexedSourceFilePaths();
  std::vector<FilePath> getCrashedSourceFilePaths();

private:
  static const char* s_sharedMemoryNamePrefix;

  static const char* s_indexingFilesKeyName;
  static const char* s_currentFilesKeyName;
  static const char* s_crashedFilesKeyName;
  static const char* s_finishedProcessIdsKeyName;
  static const char* s_indexingInterruptedKeyName;
};