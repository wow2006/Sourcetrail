#pragma once

#include "Message.h"
#include "TabId.h"

class MessageHistoryToPosition : public Message<MessageHistoryToPosition> {
public:
  static const std::string getStaticType() {
    return "MessageHistoryToPosition";
  }

  MessageHistoryToPosition(size_t index_): index(index_) {
    setSchedulerId(TabId::currentTab());
  }

  const size_t index;
};
