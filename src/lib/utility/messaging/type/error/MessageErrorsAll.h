#pragma once

#include "Message.h"

class MessageErrorsAll : public Message<MessageErrorsAll> {
public:
  static const std::string getStaticType() {
    return "MessageErrorsAll";
  }

  MessageErrorsAll() {}
};
