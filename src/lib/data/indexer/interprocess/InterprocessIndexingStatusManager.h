#pragma once

#include "BaseInterprocessDataManager.h"
namespace utility::file {
class FilePath;
} // namespace class utility::file

class InterprocessIndexingStatusManager : public BaseInterprocessDataManager {
public:
  InterprocessIndexingStatusManager(const std::string& instanceUuid, Id processId, bool isOwner);
  ~InterprocessIndexingStatusManager() override;

  void startIndexingSourceFile(const utility::file::FilePath& filePath);
  void finishIndexingSourceFile();

  void setIndexingInterrupted(bool interrupted);
  bool getIndexingInterrupted();

  Id getNextFinishedProcessId();

  std::vector<utility::file::FilePath> getCurrentlyIndexedSourceFilePaths();
  std::vector<utility::file::FilePath> getCrashedSourceFilePaths();

private:
  static const char* s_sharedMemoryNamePrefix;

  static const char* s_indexingFilesKeyName;
  static const char* s_currentFilesKeyName;
  static const char* s_crashedFilesKeyName;
  static const char* s_finishedProcessIdsKeyName;
  static const char* s_indexingInterruptedKeyName;
};