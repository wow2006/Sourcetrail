#pragma once

#include "Logger.h"
#include "Message.h"

class MessageLogFilterChanged : public Message<MessageLogFilterChanged> {
public:
  MessageLogFilterChanged(const Logger::LogLevelMask filter): logFilter(filter) {}

  static const std::string getStaticType() {
    return "MessageLogFilterChanged";
  }

  const Logger::LogLevelMask logFilter;
};