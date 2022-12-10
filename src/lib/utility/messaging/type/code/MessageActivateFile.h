#ifndef MESSAGE_ACTIVATE_FILE_H
#define MESSAGE_ACTIVATE_FILE_H

#include "FilePath.hpp"
#include "Message.h"
#include "TabId.hpp"

class MessageActivateFile : public Message<MessageActivateFile> {
 public:
  MessageActivateFile(const FilePath& filePath, unsigned int line = 0) : filePath(filePath), line(line) {
    setSchedulerId(TabId::currentTab());
  }

  static const std::string getStaticType() { return "MessageActivateFile"; }

  virtual void print(std::wostream& os) const { os << filePath.wstr(); }

  const FilePath filePath;
  unsigned int line;
};

#endif  // MESSAGE_ACTIVATE_FILE_H
