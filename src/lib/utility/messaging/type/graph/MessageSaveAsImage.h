#pragma once

#include "Message.h"


class MessageSaveAsImage : public Message<MessageSaveAsImage> {
public:
  MessageSaveAsImage(QString path_): path(std::move(path)) {}

  static const std::string getStaticType() {
    return "MessageSaveAsImage";
  }

  QString path;
};
