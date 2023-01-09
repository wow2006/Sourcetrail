#pragma once

struct LogMessage final {
  LogMessage(std::wstring message_,
             std::string filePath_,
             std::string functionName_,
             uint32_t line_,
             const std::tm& time_,
             const std::thread::id& threadId_)
      : message(std::move(message_))
      , filePath(std::move(filePath_))
      , functionName(std::move(functionName_))
      , line(line_)
      , time(time_)
      , threadId(threadId_) {}

  [[nodiscard]] std::string getTimeString(const std::string& format) const {
    constexpr auto StringSize = 50;
    std::array<char, StringSize> timeString = {};
#ifndef _WIN32
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wformat-nonliteral"
#endif
    strftime(timeString.data(), StringSize, format.c_str(), &time);
#ifndef _WIN32
#  pragma GCC diagnostic pop
#endif
    return timeString.data();
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