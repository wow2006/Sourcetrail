#pragma once

#include "Controller.h"

class RefreshView;

class RefreshController : public Controller {
public:
  RefreshController();

  ~RefreshController() override;

  virtual void clear();

private:
  RefreshView* getView();
};