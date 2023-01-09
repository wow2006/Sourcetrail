#pragma once

#include "Message.h"

class MessageSwitchColorScheme : public Message<MessageSwitchColorScheme> {
public:
  MessageSwitchColorScheme(const utility::file::FilePath& filePath): colorSchemePath(filePath) {}

  static const std::string getStaticType() {
    return "MessageSwitchColorScheme";
  }

  virtual void print(std::wostream& os) const {
    os << colorSchemePath.wstr();
  }

  const utility::file::FilePath colorSchemePath;
};
