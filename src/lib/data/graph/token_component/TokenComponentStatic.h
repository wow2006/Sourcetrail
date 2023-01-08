#pragma once

#include "TokenComponent.h"

class TokenComponentStatic : public TokenComponent {
public:
  std::shared_ptr<TokenComponent> copy() const override;
};