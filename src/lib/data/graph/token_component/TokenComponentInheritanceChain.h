#pragma once

#include "TokenComponent.h"
#include "types.h"

class TokenComponentInheritanceChain : public TokenComponent {
public:
  TokenComponentInheritanceChain(std::vector<Id> inheritanceEdgeIds_);

  std::shared_ptr<TokenComponent> copy() const override;

  const std::vector<Id> inheritanceEdgeIds;
};