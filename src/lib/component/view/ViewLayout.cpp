#include "ViewLayout.h"

ViewLayout::~ViewLayout() = default;

void ViewLayout::overrideView(View* /*view*/) {}

View* ViewLayout::findFloatingView(const std::string& /*name*/) const {
  return nullptr;
}

void ViewLayout::showOriginalViews() {}
