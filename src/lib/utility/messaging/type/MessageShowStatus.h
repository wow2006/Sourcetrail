#pragma once

#include "Message.h"

class MessageShowStatus : public Message<MessageShowStatus> {
public:
  MessageShowStatus() {}

  static const std::string getStaticType() {
    return "MessageShowStatus";
  }
};
