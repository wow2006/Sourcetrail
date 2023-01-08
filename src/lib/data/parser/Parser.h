#pragma once

class ParserClient;

class Parser {
public:
  Parser(std::shared_ptr<ParserClient> client);
  virtual ~Parser() = default;

protected:
  std::shared_ptr<ParserClient> m_client;
};
