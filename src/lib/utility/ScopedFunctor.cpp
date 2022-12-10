#include "ScopedFunctor.hpp"

ScopedFunctor::ScopedFunctor(std::function<void(void)> onDestroy) noexcept : m_onDestroy(std::move(onDestroy)) {}

ScopedFunctor::~ScopedFunctor() { m_onDestroy(); }
