#pragma once

#include "Message.h"

class MessageClearStatusView : public Message<MessageClearStatusView> {
public:
  MessageClearStatusView() {}

  static const std::string getStaticType() {
    return "MessageClearStatusView";
  }
};
