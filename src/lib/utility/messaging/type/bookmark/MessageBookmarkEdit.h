#pragma once

#include "Message.h"

class MessageBookmarkEdit : public Message<MessageBookmarkEdit> {
public:
  static const std::string getStaticType() {
    return "MessageBookmarkEdit";
  }
};
