#include "TokenComponentInheritanceChain.h"

TokenComponentInheritanceChain::TokenComponentInheritanceChain(std::vector<Id> inheritanceEdgeIds_)
    : inheritanceEdgeIds(std::move(inheritanceEdgeIds_)) {}

std::shared_ptr<TokenComponent> TokenComponentInheritanceChain::copy() const {
  return std::make_shared<TokenComponentInheritanceChain>(*this);
}