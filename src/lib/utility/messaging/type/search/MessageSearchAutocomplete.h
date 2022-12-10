#ifndef MESSAGE_SEARCH_AUTOCOMPLETE_H
#define MESSAGE_SEARCH_AUTOCOMPLETE_H

#include "Message.h"
#include "Node.h"
#include "NodeTypeSet.h"
#include "TabId.hpp"

class MessageSearchAutocomplete : public Message<MessageSearchAutocomplete> {
 public:
  MessageSearchAutocomplete(const std::wstring& query, NodeTypeSet acceptedNodeTypes)
      : query(query), acceptedNodeTypes(acceptedNodeTypes) {
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() { return "MessageSearchAutocomplete"; }

  virtual void print(std::wostream& os) const {
    os << query << L"[";
    std::vector<Id> nodeTypeIds = acceptedNodeTypes.getNodeTypeIds();
    for (size_t i = 0; i < nodeTypeIds.size(); i++) {
      if (i != 0) {
        os << L", ";
      }
      os << std::to_wstring(nodeTypeIds[i]);
    }
    os << L"]";
  }

  const std::wstring query;
  const NodeTypeSet acceptedNodeTypes;
};

#endif  // MESSAGE_SEARCH_AUTOCOMPLETE_H
