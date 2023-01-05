#pragma once

#include "MessageBase.h"
#include "MessageListenerBase.h"
#include "MessageQueue.h"

template <typename MessageType>
class MessageListener : public MessageListenerBase {
public:
  MessageListener() = default;

private:
  virtual std::string doGetType() const {
    return MessageType::getStaticType();
  }

  virtual void doHandleMessageBase(MessageBase* message) {
    handleMessage(dynamic_cast<MessageType*>(message));
  }

  virtual void handleMessage(MessageType* message) = 0;
};