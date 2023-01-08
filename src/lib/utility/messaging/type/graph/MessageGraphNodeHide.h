#pragma once

#include "Message.h"
#include "TabId.h"
#include "types.h"

class MessageGraphNodeHide : public Message<MessageGraphNodeHide> {
public:
  MessageGraphNodeHide(Id tokenId_): tokenId(tokenId_) {
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() {
    return "MessageGraphNodeHide";
  }

  virtual void print(std::wostream& os) const {
    os << tokenId;
  }

  const Id tokenId;
};
