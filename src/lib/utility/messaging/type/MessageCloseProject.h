#pragma once

#include "FilePath.hpp"
#include "Message.h"
#include "RefreshInfo.h"

class MessageCloseProject : public Message<MessageCloseProject> {
 public:
  MessageCloseProject() {}

  static const std::string getStaticType() { return "MessageCloseProject"; }

  virtual void print([[maybe_unused]] std::wostream& os) const {}
};
