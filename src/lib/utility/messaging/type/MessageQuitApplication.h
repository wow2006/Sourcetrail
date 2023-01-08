#pragma once

#include "Message.h"

class MessageQuitApplication : public Message<MessageQuitApplication> {
public:
  MessageQuitApplication() {}

  static const std::string getStaticType() {
    return "MessageQuitApplication";
  }
};
