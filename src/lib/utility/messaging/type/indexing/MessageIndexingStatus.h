#ifndef MESSAGE_INDEXING_STATUS_H
#define MESSAGE_INDEXING_STATUS_H

#include "Message.h"

class MessageIndexingStatus : public Message<MessageIndexingStatus> {
 public:
  static const std::string getStaticType() { return "MessageIndexingStatus"; }

  MessageIndexingStatus(bool showProgress, size_t progressPercent = 0)
      : showProgress(showProgress), progressPercent(progressPercent) {
    setSendAsTask(false);
  }

  const bool showProgress;
  const size_t progressPercent;
};

#endif  // MESSAGE_INDEXING_STATUS_H
