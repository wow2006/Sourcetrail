#pragma once

class TokenComponent {
public:
  virtual ~TokenComponent();
  virtual std::shared_ptr<TokenComponent> copy() const = 0;
};