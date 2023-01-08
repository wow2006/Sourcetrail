#include "TokenComponentIsAmbiguous.h"

std::shared_ptr<TokenComponent> TokenComponentIsAmbiguous::copy() const {
  return std::make_shared<TokenComponentIsAmbiguous>(*this);
}