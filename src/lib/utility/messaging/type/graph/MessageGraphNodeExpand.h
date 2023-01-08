#pragma once

#include "Message.h"
#include "TabId.h"
#include "types.h"

class MessageGraphNodeExpand : public Message<MessageGraphNodeExpand> {
public:
  MessageGraphNodeExpand(Id tokenId_, bool expand_, bool ignoreIfNotReplayed_ = false)
      : tokenId(tokenId_), expand(expand_), ignoreIfNotReplayed(ignoreIfNotReplayed_) {
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() {
    return "MessageGraphNodeExpand";
  }

  virtual void print(std::wostream& os) const {
    os << tokenId << L" ";
    if(expand) {
      os << L"expand";
    } else {
      os << L"collapse";
    }
  }

  const Id tokenId;
  const bool expand;
  const bool ignoreIfNotReplayed;
};
