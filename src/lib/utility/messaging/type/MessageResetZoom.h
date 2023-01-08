#pragma once

#include "Message.h"

class MessageResetZoom : public Message<MessageResetZoom> {
public:
  MessageResetZoom() {}

  static const std::string getStaticType() {
    return "MessageResetZoom";
  }
};
