#pragma once

#include "Message.h"

class MessageTabClose : public Message<MessageTabClose> {
public:
  static const std::string getStaticType() {
    return "MessageTabClose";
  }
};
