#pragma once

#include "QtWindow.h"

class QtAbout : public QtWindow {
public:
  QtAbout(QWidget* parent = 0);

  QSize sizeHint() const override;

  void setupAbout();
};