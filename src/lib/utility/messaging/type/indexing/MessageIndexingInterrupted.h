#pragma once

#include "Message.h"

class MessageIndexingInterrupted : public Message<MessageIndexingInterrupted> {
public:
  static const std::string getStaticType() {
    return "MessageIndexingInterrupted";
  }

  MessageIndexingInterrupted() {
    setSendAsTask(false);
  }
};
