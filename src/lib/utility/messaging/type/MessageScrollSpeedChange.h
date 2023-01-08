#pragma once

#include "Message.h"

class MessageScrollSpeedChange : public Message<MessageScrollSpeedChange> {
public:
  MessageScrollSpeedChange(float scrollSpeed_): scrollSpeed(scrollSpeed_) {}

  static const std::string getStaticType() {
    return "MessageScrollSpeedChange";
  }

  virtual void print(std::wostream& os) const {
    os << scrollSpeed;
  }

  const float scrollSpeed;
};
