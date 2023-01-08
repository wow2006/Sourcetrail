#pragma once

#include "Message.h"

class MessageIndexingFinished : public Message<MessageIndexingFinished> {
public:
  static const std::string getStaticType() {
    return "MessageIndexingFinished";
  }

  MessageIndexingFinished() {}
};
