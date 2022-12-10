#pragma once

#include <functional>

class ScopedFunctor final {
 public:
  explicit ScopedFunctor(std::function<void(void)> onDestroy) noexcept;

  ~ScopedFunctor();

  ScopedFunctor(const ScopedFunctor&) = delete;
  ScopedFunctor(ScopedFunctor&&) = delete;

  ScopedFunctor operator=(const ScopedFunctor&) = delete;
  ScopedFunctor operator=(ScopedFunctor&&) = delete;

 private:
  std::function<void(void)> m_onDestroy;
};
