#pragma once

#include "AccessKind.h"
#include "TokenComponent.h"

class TokenComponentAccess : public TokenComponent {
public:
  static std::wstring getAccessString(AccessKind access);

  TokenComponentAccess(AccessKind access);

  ~TokenComponentAccess() override;

  virtual std::shared_ptr<TokenComponent> copy() const;

  AccessKind getAccess() const;
  std::wstring getAccessString() const;

private:
  const AccessKind m_access;
};