#pragma once

#include "Message.h"
#include "TabId.h"

class MessageShowError : public Message<MessageShowError> {
public:
  static const std::string getStaticType() {
    return "MessageShowError";
  }

  MessageShowError(Id errorId_): errorId(errorId_) {
    setSchedulerId(TabId::currentTab());
  }

  const Id errorId;
};
