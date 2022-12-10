#pragma once

#include <cstdint>
#include <ctime>
#include <string>
#include <thread>

struct LogMessage final {
  LogMessage(std::wstring message, std::string filePath, std::string functionName,
             uint32_t line, const std::tm& time, std::thread::id threadId);

  [[nodiscard]] std::string getTimeString(std::string_view format) const;

  [[nodiscard]] std::string getFileName() const;

  const std::wstring m_message;
  const std::string m_filePath;
  const std::string m_functionName;
  const unsigned int m_line;
  const std::tm m_time;
  const std::thread::id m_threadId;
};
