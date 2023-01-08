#pragma once

#include "Message.h"

class MessageIndexingStarted : public Message<MessageIndexingStarted> {
public:
  static const std::string getStaticType() {
    return "MessageIndexingStarted";
  }

  MessageIndexingStarted() {}
};
