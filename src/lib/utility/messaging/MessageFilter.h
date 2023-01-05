#pragma once

#include "MessageQueue.h"

class MessageFilter {
public:
  virtual ~MessageFilter() = default;

  virtual void filter(MessageQueue::MessageBufferType* messageBuffer) = 0;
};