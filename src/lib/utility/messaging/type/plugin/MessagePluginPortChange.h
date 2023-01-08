#pragma once

#include "Message.h"

class MessagePluginPortChange : public Message<MessagePluginPortChange> {
public:
  MessagePluginPortChange() {}

  static const std::string getStaticType() {
    return "MessagePluginPortChange";
  }
};
