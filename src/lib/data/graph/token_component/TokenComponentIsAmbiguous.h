#pragma once

#include "TokenComponent.h"

class TokenComponentIsAmbiguous : public TokenComponent {
public:
  std::shared_ptr<TokenComponent> copy() const override;
};