#pragma once

#include "Message.h"
#include "TabId.h"

class MessageFocusedSearchView : public Message<MessageFocusedSearchView> {
public:
  MessageFocusedSearchView(bool focusIn_): focusIn(focusIn_) {
    setIsLogged(false);
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() {
    return "MessageFocusedSearchView";
  }

  const bool focusIn;
};
