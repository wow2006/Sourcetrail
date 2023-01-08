#pragma once

#include "Message.h"

class MessageCustomTrailShow : public Message<MessageCustomTrailShow> {
public:
  MessageCustomTrailShow() {}

  static const std::string getStaticType() {
    return "MessageCustomTrailShow";
  }
};
