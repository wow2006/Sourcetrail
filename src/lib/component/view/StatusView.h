#pragma once

#include "Status.h"
#include "View.h"

namespace utility {
struct Status;
} // namespace utility

class StatusView : public View {
public:
  explicit StatusView(ViewLayout* viewLayout);

  ~StatusView() override;

  [[nodiscard]] std::string getName() const override;

  virtual void addStatus(const std::vector<utility::Status>& status) = 0;

  virtual void clear() = 0;
};
