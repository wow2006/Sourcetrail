#pragma once

#include "Message.h"

class MessageProjectEdit : public Message<MessageProjectEdit> {
public:
  MessageProjectEdit() {}

  static const std::string getStaticType() {
    return "MessageProjectEdit";
  }
};
