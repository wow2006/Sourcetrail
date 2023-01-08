#pragma once

#include "Message.h"

class MessageWindowChanged : public Message<MessageWindowChanged> {
public:
  static const std::string getStaticType() {
    return "MessageWindowChanged";
  }
};
