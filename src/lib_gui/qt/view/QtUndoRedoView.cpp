#include "QtUndoRedoView.h"

#include "QtViewWidgetWrapper.h"
#include "ResourcePaths.hpp"
#include "utilityQt.h"

QtUndoRedoView::QtUndoRedoView(ViewLayout* viewLayout) : UndoRedoView(viewLayout) { m_widget = new QtUndoRedo(); }

void QtUndoRedoView::createWidgetWrapper() { setWidgetWrapper(std::make_shared<QtViewWidgetWrapper>(m_widget)); }

void QtUndoRedoView::refreshView() {
  m_onQtThread([=]() {
    m_widget->setStyleSheet(
        utility::getStyleSheet(resourcePaths::getGuiDirectoryPath().concatenate(L"undoredo_view/undoredo_view.css"))
            .c_str());
  });
}

void QtUndoRedoView::setRedoButtonEnabled(bool enabled) {
  m_onQtThread([=]() { m_widget->setRedoButtonEnabled(enabled); });
}

void QtUndoRedoView::setUndoButtonEnabled(bool enabled) {
  m_onQtThread([=]() { m_widget->setUndoButtonEnabled(enabled); });
}

void QtUndoRedoView::updateHistory(const std::vector<SearchMatch>& searchMatches, size_t currentIndex) {
  m_onQtThread([=]() { m_widget->updateHistory(searchMatches, currentIndex); });
}
