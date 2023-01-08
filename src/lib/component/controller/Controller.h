#pragma once

#include "Component.h"

class Controller {
public:
  Controller();

  virtual ~Controller();

  void setComponent(Component* component);

  virtual void clear() = 0;

  Id getTabId() const;

protected:
  template <typename ViewType>
  ViewType* getView() const;

private:
  Component* m_component;
};


template <typename ViewType>
ViewType* Controller::getView() const {
  if(m_component) {
    return m_component->getView<ViewType>();
  }

  return nullptr;
}