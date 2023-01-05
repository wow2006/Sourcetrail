#pragma once

#include "Bookmark.h"
#include "BookmarkController.h"
#include "ControllerProxy.h"
#include "QtWindow.h"

QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QTreeWidget)
QT_FORWARD_DECLARE_CLASS(QTreeWidgetItem)

class QtBookmarkBrowser : public QtWindow {
  Q_OBJECT

public:
  QtBookmarkBrowser(ControllerProxy<BookmarkController>* controllerProxy, QWidget* parent = nullptr);

  ~QtBookmarkBrowser() override;

  void setupBookmarkBrowser();

  void setBookmarks(const std::vector<std::shared_ptr<Bookmark>>& bookmarks);

protected:
  void resizeEvent(QResizeEvent* event) override;

  void handleClose() override;
  void handleNext() override;

private slots:
  void filterOrOrderChanged(int index);
  void treeItemClicked(QTreeWidgetItem* item, int column);

private:
  Bookmark::BookmarkFilter getSelectedFilter();
  Bookmark::BookmarkOrder getSelectedOrder();

  QTreeWidgetItem* findOrCreateTreeCategory(const BookmarkCategory& category);

  ControllerProxy<BookmarkController>* m_controllerProxy;

  QTreeWidget* m_bookmarkTree;

  QComboBox* m_filterComboBox;
  QComboBox* m_orderComboBox;
  std::vector<std::string> m_orderNames;

  QWidget* m_headerBackground;
};