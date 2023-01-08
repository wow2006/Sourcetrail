#pragma once

#include "Message.h"

class MessageZoom : public Message<MessageZoom> {
public:
  MessageZoom(bool zoomIn_): zoomIn(zoomIn_) {}

  static const std::string getStaticType() {
    return "MessageZoom";
  }

  virtual void print(std::wostream& os) const {
    if(zoomIn) {
      os << L"in";
    } else {
      os << L"out";
    }
  }

  const bool zoomIn;
};
