#pragma once

#include "Message.h"
#include "TabId.h"

class MessageHistoryRedo : public Message<MessageHistoryRedo> {
public:
  static const std::string getStaticType() {
    return "MessageHistoryRedo";
  }

  MessageHistoryRedo() {
    setSchedulerId(TabId::currentTab());
  }
};
