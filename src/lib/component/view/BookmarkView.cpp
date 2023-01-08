#include "BookmarkView.h"

#include "BookmarkController.h"

BookmarkView::BookmarkView(ViewLayout* viewLayout): View(viewLayout) {}

BookmarkView::~BookmarkView() = default;

std::string BookmarkView::getName() const {
  return "BookmarkView";
}

BookmarkController* BookmarkView::getController() {
  return View::getController<BookmarkController>();
}
