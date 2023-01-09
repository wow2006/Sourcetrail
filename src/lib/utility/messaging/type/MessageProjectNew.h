#pragma once

#include "FilePath.h"
#include "Message.h"

class MessageProjectNew : public Message<MessageProjectNew> {
public:
  MessageProjectNew(const utility::file::FilePath& cdbPath_): cdbPath(cdbPath_) {}

  static const std::string getStaticType() {
    return "MessageProjectNew";
  }

  const utility::file::FilePath cdbPath;
};
