#pragma once
// STL
#include <ctime>
#include <string>
#include <thread>

struct LogMessage final {
public:
  LogMessage(const std::wstring& message_,
             const std::string& filePath_,
             const std::string& functionName_,
             const unsigned int line_,
             const std::tm& time_,
             const std::thread::id& threadId_)
      : message(message_)
      , filePath(filePath_)
      , functionName(functionName_)
      , line(line_)
      , time(time_)
      , threadId(threadId_) {}

  [[nodiscard]] std::string getTimeString(const std::string& format) const {
    char timeString[50];
#ifndef _WIN32
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#endif
    strftime(timeString, 50, format.c_str(), &time);
#ifndef _WIN32
#pragma GCC diagnostic pop
#endif
    return timeString;
  }

  [[nodiscard]] std::string getFileName() const {
    return filePath.substr(filePath.find_last_of("/\\") + 1);
  }

  const std::wstring message;
  const std::string filePath;
  const std::string functionName;
  const unsigned int line;
  const std::tm time;
  const std::thread::id threadId;
};