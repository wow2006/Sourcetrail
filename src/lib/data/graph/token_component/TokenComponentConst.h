#pragma once

#include "TokenComponent.h"

class TokenComponentConst : public TokenComponent {
public:
  std::shared_ptr<TokenComponent> copy() const override;
};