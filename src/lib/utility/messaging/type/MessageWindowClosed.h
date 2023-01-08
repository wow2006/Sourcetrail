#pragma once

#include "Message.h"

class MessageWindowClosed : public Message<MessageWindowClosed> {
public:
  MessageWindowClosed() {
    setSendAsTask(false);
  }

  static const std::string getStaticType() {
    return "MessageWindowClosed";
  }
};
