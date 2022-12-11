// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "ScopedFunctor.hpp"

ScopedFunctor::ScopedFunctor(std::function<void(void)> onDestroy) noexcept : m_onDestroy(std::move(onDestroy)) {}

ScopedFunctor::~ScopedFunctor() { m_onDestroy(); }
