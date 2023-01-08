#pragma once

#include "TooltipInfo.h"
#include "View.h"

class TooltipView : public View {
public:
  TooltipView(ViewLayout* viewLayout);

  ~TooltipView() override;

  // View implementation
  virtual std::string getName() const;

  virtual void showTooltip(const TooltipInfo& info, const View* parent) = 0;
  virtual void hideTooltip(bool force) = 0;

  virtual bool tooltipVisible() const = 0;
};