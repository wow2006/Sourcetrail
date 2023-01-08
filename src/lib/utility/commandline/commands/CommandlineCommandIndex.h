#pragma once

#include "CommandlineCommand.h"

namespace commandline {

class CommandlineCommandIndex : public CommandlineCommand {
public:
  CommandlineCommandIndex(CommandLineParser* parser);
  virtual ~CommandlineCommandIndex();

  virtual void setup();
  virtual ReturnStatus parse(std::vector<std::string>& args);

  virtual bool hasHelp() const {
    return true;
  }
};

}    // namespace commandline
