#pragma once

template <class T>
class Color {
public:
  static Color<T> fromString(const std::string& str);

  Color();
  Color(T r_, T g_, T b_, T a_);

  [[nodiscard]] std::string toString() const;

  T r, g, b, a;
};

template <class T>
Color<T> Color<T>::fromString(const std::string& str) {
  Color<T> color;
  std::stringstream stringstream;
  stringstream << str;
  stringstream >> color.r >> color.g >> color.b >> color.a;
  return color;
}

template <class T>
Color<T>::Color(): r(0), g(0), b(0), a(0) {}

template <class T>
Color<T>::Color(T r_, T g_, T b_, T a_): r(r_), g(g_), b(b_), a(a_) {}

template <class T>
std::string Color<T>::toString() const {
  return fmt::format("{} {} {} {}", r, g, b, a);
}

using Colorf = Color<float>;
using Colori = Color<int>;