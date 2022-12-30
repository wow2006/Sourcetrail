#pragma once

#include <QString>

class QWidget;

class QtHelpButtonInfo {
public:
  QtHelpButtonInfo(QString helpTitle, QString helpText);

  void displayMessage(QWidget* messageBoxParent);

private:
  QString m_title;
  QString m_text;
};

QtHelpButtonInfo createErrorHelpButtonInfo();
