#pragma once

#include "Message.h"
#include "TabId.h"

class MessageHistoryUndo : public Message<MessageHistoryUndo> {
public:
  static const std::string getStaticType() {
    return "MessageHistoryUndo";
  }

  MessageHistoryUndo() {
    setSchedulerId(TabId::currentTab());
  }
};
