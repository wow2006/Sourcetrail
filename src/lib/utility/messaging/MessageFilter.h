#ifndef MESSAGE_FILTER_H
#define MESSAGE_FILTER_H

#include "MessageQueue.hpp"

class MessageFilter {
 public:
  virtual ~MessageFilter() {}

  virtual void filter(MessageQueue::MessageBufferType* messageBuffer) = 0;
};

#endif  // MESSAGE_FILTER_H
