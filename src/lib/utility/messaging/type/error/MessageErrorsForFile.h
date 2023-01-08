#pragma once

#include "Message.h"

class MessageErrorsForFile : public Message<MessageErrorsForFile> {
public:
  static const std::string getStaticType() {
    return "MessageErrorsForFile";
  }

  MessageErrorsForFile(const FilePath& file_): file(file) {}

  const FilePath& file;
};
