#pragma once

#include "Message.h"

class MessageIDECreateCDB : public Message<MessageIDECreateCDB> {
public:
  MessageIDECreateCDB() {}

  static const std::string getStaticType() {
    return "MessageIDECreateCDB";
  }

  virtual void print(std::wostream& os) const {
    os << L"Create CDB from current solution";
  }
};
