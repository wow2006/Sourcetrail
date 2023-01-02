#pragma once

#include "Message.h"
#include "Status.h"

class MessageStatusFilterChanged : public Message<MessageStatusFilterChanged> {
public:
  explicit MessageStatusFilterChanged(utility::StatusFilter filter): statusFilter(filter) {}

  static std::string getStaticType() {
    return "MessageStatusFilterChanged";
  }

  const utility::StatusFilter statusFilter;
};
