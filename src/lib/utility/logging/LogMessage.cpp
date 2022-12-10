#include "LogMessage.hpp"

#include <array>
#include <iostream>

constexpr size_t ARRAY_SIZE = 50;

LogMessage::LogMessage(std::wstring message, std::string filePath, std::string functionName,
                       unsigned int line, const std::tm& time, std::thread::id threadId)
    : m_message(std::move(message)),
      m_filePath(std::move(filePath)),
      m_functionName(std::move(functionName)),
      m_line(line),
      m_time(time),
      m_threadId(threadId) {}

std::string LogMessage::getTimeString(std::string_view format) const {
  std::array<char, ARRAY_SIZE> timeString{};
  if(strftime(timeString.data(), ARRAY_SIZE, format.data(), &m_time) == 0) {
    std::cerr << "strftime failed";
  }
  return timeString.data();
}

std::string LogMessage::getFileName() const { return m_filePath.substr(m_filePath.find_last_of("/\\") + 1); }
