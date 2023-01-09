#pragma once

#include "Message.h"

class MessageQuitApplication : public Message<MessageQuitApplication> {
public:
  MessageQuitApplication();

  ~MessageQuitApplication() override;

  static std::string getStaticType();
};
