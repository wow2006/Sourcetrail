#pragma once

#include "Message.h"
#include "TabId.h"
#include "types.h"

class MessageActivateLocalSymbols : public Message<MessageActivateLocalSymbols> {
public:
  MessageActivateLocalSymbols(const std::vector<Id>& symbolIds_): symbolIds(symbolIds_) {
    setSchedulerId(TabId::currentTab());
  }

  void addSymbol(Id symbolId) {
    symbolIds.push_back(symbolId);
  }

  static const std::string getStaticType() {
    return "MessageActivateLocalSymbols";
  }

  virtual void print(std::wostream& os) const {
    for(const Id& symbolId: symbolIds) {
      os << symbolId << L" ";
    }
  }

  std::vector<Id> symbolIds;
};
