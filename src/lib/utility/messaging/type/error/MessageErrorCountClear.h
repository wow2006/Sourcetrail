#pragma once

#include "Message.h"

class MessageErrorCountClear : public Message<MessageErrorCountClear> {
public:
  static const std::string getStaticType() {
    return "MessageErrorCountClear";
  }

  MessageErrorCountClear() {
    setSendAsTask(false);
  }
};
