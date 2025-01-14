#ifndef MESSAGE_SCROLL_TO_LINE_H
#define MESSAGE_SCROLL_TO_LINE_H

#include "FilePath.hpp"
#include "Message.h"
#include "TabId.hpp"

class MessageScrollToLine : public Message<MessageScrollToLine> {
 public:
  MessageScrollToLine(const FilePath& filePath, size_t line) : filePath(filePath), line(line) {
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() { return "MessageScrollToLine"; }

  void print(std::wostream& os) const override { os << filePath.wstr() << L":" << line; }

  const FilePath filePath;
  size_t line;
};

#endif  // MESSAGE_SCROLL_TO_LINE_H
