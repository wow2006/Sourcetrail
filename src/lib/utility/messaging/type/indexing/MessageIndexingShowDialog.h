#pragma once

#include "Message.h"

class MessageIndexingShowDialog : public Message<MessageIndexingShowDialog> {
public:
  static const std::string getStaticType() {
    return "MessageIndexingShowDialog";
  }

  MessageIndexingShowDialog() {
    setSendAsTask(false);
  }
};
