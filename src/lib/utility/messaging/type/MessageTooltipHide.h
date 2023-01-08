#pragma once

#include "Message.h"

class MessageTooltipHide : public Message<MessageTooltipHide> {
public:
  MessageTooltipHide() {
    setSendAsTask(false);
    setIsLogged(false);
  }

  static const std::string getStaticType() {
    return "MessageTooltipHide";
  }
};
