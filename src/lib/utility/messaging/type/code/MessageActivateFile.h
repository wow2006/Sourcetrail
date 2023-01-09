#pragma once

#include "FilePath.h"
#include "Message.h"
#include "TabId.h"

class MessageActivateFile : public Message<MessageActivateFile> {
public:
  MessageActivateFile(const utility::file::FilePath& filePath_, unsigned int line_ = 0)
      : filePath(filePath_), line(line_) {
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() {
    return "MessageActivateFile";
  }

  virtual void print(std::wostream& os) const {
    os << filePath.wstr();
  }

  const utility::file::FilePath filePath;
  unsigned int line;
};
