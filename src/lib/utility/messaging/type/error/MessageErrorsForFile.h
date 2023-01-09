#pragma once

#include "Message.h"

class MessageErrorsForFile : public Message<MessageErrorsForFile> {
public:
  static const std::string getStaticType() {
    return "MessageErrorsForFile";
  }

  MessageErrorsForFile(const utility::file::FilePath& file_): file(file) {}

  const utility::file::FilePath& file;
};
