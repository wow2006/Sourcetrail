#pragma once

#include "Message.h"
#include "TabId.h"

class MessageFocusedSearchView : public Message<MessageFocusedSearchView> {
 public:
  MessageFocusedSearchView(bool focusIn) : m_focusIn(focusIn) {
    setIsLogged(false);
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() { return "MessageFocusedSearchView"; }

  const bool m_focusIn;
};
