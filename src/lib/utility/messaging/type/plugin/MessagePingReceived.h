#pragma once

#include "Message.h"

class MessagePingReceived : public Message<MessagePingReceived> {
public:
  MessagePingReceived(): ideName(L"") {}

  static const std::string getStaticType() {
    return "MessagePingReceived";
  }

  std::wstring ideName;
};
