#pragma once

#include "FilePath.h"
#include "LogMessage.h"
#include "Logger.h"

class FileLogger : public Logger {
public:
  static std::wstring generateDatedFileName(const std::wstring& prefix = L"",
                                            const std::wstring& suffix = L"",
                                            int offsetDays = 0);

  FileLogger();

  FilePath getLogFilePath() const;
  void setLogFilePath(const FilePath& filePath);

  void setLogDirectory(const FilePath& filePath);
  void setFileName(const std::wstring& fileName);
  void setMaxLogLineCount(uint32_t logCount);

  // setting the max log file count to 0 will disable ringlogging
  void setMaxLogFileCount(uint32_t amount);

  void deleteLogFiles(const std::wstring& cutoffDate);

private:
  void logInfo(const LogMessage& message) override;
  void logWarning(const LogMessage& message) override;
  void logError(const LogMessage& message) override;

  void logMessage(const std::string& type, const LogMessage& message);
  void updateLogFileName();

  std::wstring m_logFileName;
  FilePath m_logDirectory;
  FilePath m_currentLogFilePath;

  uint32_t m_maxLogLineCount;
  uint32_t m_maxLogFileCount;
  uint32_t m_currentLogLineCount;
  uint32_t m_currentLogFileCount;
};