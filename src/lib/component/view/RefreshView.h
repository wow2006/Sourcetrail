#pragma once

#include "View.h"

class RefreshController;

class RefreshView : public View {
public:
  RefreshView(ViewLayout* viewLayout);

  ~RefreshView() override;

  virtual std::string getName() const;

private:
  RefreshController* getController();
};