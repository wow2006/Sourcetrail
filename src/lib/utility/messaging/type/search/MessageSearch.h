#pragma once

#include "Message.h"

#include "NodeTypeSet.h"
#include "SearchMatch.h"
#include "TabId.h"

class MessageSearch : public Message<MessageSearch> {
public:
  static const std::string getStaticType() {
    return "MessageSearch";
  }

  MessageSearch(const std::vector<SearchMatch>& matches_, NodeTypeSet acceptedNodeTypes_)
      : acceptedNodeTypes(acceptedNodeTypes_), m_matches(matches_) {
    setSchedulerId(TabId::currentTab());
  }

  const std::vector<SearchMatch>& getMatches() const {
    return m_matches;
  }

  virtual void print(std::wostream& os) const {
    for(const SearchMatch& match: m_matches) {
      os << " @" << match.name;
      for(Id id: match.tokenIds) {
        os << ' ' << id;
      }
    }
  }

  NodeTypeSet acceptedNodeTypes;

private:
  const std::vector<SearchMatch> m_matches;
};
