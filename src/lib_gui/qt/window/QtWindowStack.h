#pragma once

#include <QWidget>

class QtWindowStackElement : public QWidget {
  Q_OBJECT
public:
  QtWindowStackElement(QWidget* parent = nullptr);

  virtual void showWindow() = 0;

  virtual void hideWindow() = 0;
};


class QtWindowStack : public QObject {
  Q_OBJECT

signals:
  void empty();

  void pop();

  void push();

public:
  QtWindowStack(QObject* parent = nullptr);

  QtWindowStackElement* getTopWindow() const;

  QtWindowStackElement* getBottomWindow() const;

  size_t getWindowCount() const;

  void centerSubWindows();

public slots:
  void pushWindow(QtWindowStackElement* window);

  void popWindow();

  void clearWindows();

private:
  std::vector<QtWindowStackElement*> m_stack;
};