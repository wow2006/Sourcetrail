#pragma once

#include "FilePath.h"
#include "Message.h"
#include "TabId.h"

class MessageScrollToLine : public Message<MessageScrollToLine> {
public:
  MessageScrollToLine(const FilePath& filePath_, size_t line_): filePath(filePath_), line(line_) {
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() {
    return "MessageScrollToLine";
  }

  void print(std::wostream& os) const override {
    os << filePath.wstr() << L":" << line;
  }

  const FilePath filePath;
  size_t line;
};
