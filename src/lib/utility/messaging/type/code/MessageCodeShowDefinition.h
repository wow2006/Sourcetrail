#ifndef MESSAGE_CODE_SHOW_DEFINITION_H
#define MESSAGE_CODE_SHOW_DEFINITION_H

#include "Message.h"
#include "TabId.hpp"
#include "types.hpp"

class MessageCodeShowDefinition : public Message<MessageCodeShowDefinition> {
 public:
  static const std::string getStaticType() { return "MessageCodeShowDefinition"; }

  MessageCodeShowDefinition(Id nodeId, bool inIDE = false) : nodeId(nodeId), inIDE(inIDE) {
    setSchedulerId(TabId::currentTab());
  }

  virtual void print(std::wostream& os) const { os << nodeId; }

  const Id nodeId;
  const bool inIDE;
};

#endif  // MESSAGE_CODE_SHOW_DEFINITION_H
