#pragma once

#include "CommandlineCommand.h"

namespace commandline {

class CommandlineCommandIndex final : public CommandlineCommand {
 public:
  explicit CommandlineCommandIndex(CommandLineParser* parser);

  ~CommandlineCommandIndex() override;

  void setup() override;

  ReturnStatus parse(std::vector<std::string>& args) override;

  bool hasHelp() const  override;

};

}  // namespace commandline
