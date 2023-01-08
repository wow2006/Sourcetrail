#pragma once

#include "TokenComponent.h"

class TokenComponentAbstraction : public TokenComponent {
public:
  enum AbstractionType { ABSTRACTION_VIRTUAL, ABSTRACTION_PURE_VIRTUAL, ABSTRACTION_NONE };

  TokenComponentAbstraction(AbstractionType abstraction);
  ~TokenComponentAbstraction() override;

  virtual std::shared_ptr<TokenComponent> copy() const;

  AbstractionType getAbstraction() const;
  std::string getAbstractionString() const;

private:
  const AbstractionType m_abstraction;
};