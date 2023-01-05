#pragma once

#include <QApplication>

class QtApplication : public QApplication {
  Q_OBJECT
public:
  QtApplication(int& argc, char** argv);

  bool event(QEvent* event);
  int exec();

private slots:
  void onApplicationStateChanged(Qt::ApplicationState state);
};