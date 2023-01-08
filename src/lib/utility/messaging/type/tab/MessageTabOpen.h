#pragma once

#include "Message.h"

class MessageTabOpen : public Message<MessageTabOpen> {
public:
  static const std::string getStaticType() {
    return "MessageTabOpen";
  }
};
