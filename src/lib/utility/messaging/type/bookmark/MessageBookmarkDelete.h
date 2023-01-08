#pragma once

#include "Message.h"

class MessageBookmarkDelete : public Message<MessageBookmarkDelete> {
public:
  static const std::string getStaticType() {
    return "MessageBookmarkDelete";
  }
};
