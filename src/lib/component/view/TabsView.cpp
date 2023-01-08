#include "TabsView.h"

TabsView::TabsView(ViewLayout* viewLayout): View(viewLayout) {}

TabsView::~TabsView() = default;

std::string TabsView::getName() const {
  return "Tabs";
}
