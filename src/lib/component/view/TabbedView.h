#pragma once

#include "View.h"
#include "ViewLayout.h"

class TabbedView
    : public View
    , public ViewLayout {
public:
  TabbedView(ViewLayout* viewLayout, const std::string& name);

  ~TabbedView() override;

  const std::vector<View*>& getViews() const;

  virtual void addViewWidget(View* view) = 0;

  // View implementation
  virtual std::string getName() const;

  // ViewLayout implementation
  virtual void addView(View* view);
  virtual void removeView(View* view);

  virtual void showView(View* view);
  virtual void hideView(View* view);

  virtual void setViewEnabled(View* view, bool enabled);

private:
  std::vector<View*> m_views;
  std::string m_name;
};