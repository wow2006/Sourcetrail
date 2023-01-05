#pragma once

template <typename T>
class ScopedSwitcher {
public:
  ScopedSwitcher(T& var): m_var(&var), m_origVal(var) {}

  ScopedSwitcher(T& var, T tempVal): m_var(&var), m_origVal(var) {
    var = tempVal;
  }

  ~ScopedSwitcher() {
    *m_var = m_origVal;
  }

private:
  T* m_var;
  T m_origVal;
};