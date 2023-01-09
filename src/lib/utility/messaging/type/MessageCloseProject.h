#pragma once

#include "RefreshInfo.h"

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "Message.h"

class MessageCloseProject : public Message<MessageCloseProject> {
public:
  MessageCloseProject() {}

  static const std::string getStaticType() {
    return "MessageCloseProject";
  }

  virtual void print(std::wostream& /*os*/) const {}
};
