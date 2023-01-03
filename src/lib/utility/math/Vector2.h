#pragma once

#include "Property.h"
#include "logging.h"

#include "VectorBase.h"

template <class T>
class Vector2 : public VectorBase<T, 2> {
public:
  Vector2();
  Vector2(const T& x_, const T& y_);
  Vector2(const VectorBase<T, 2>& vector);
  Vector2(const Vector2<T>& vector);
  virtual ~Vector2();

  T getValue(uint32_t index) const;
  void setValue(uint32_t index, const T& value);

  T operator[](uint32_t index);

  Property<T> x;
  Property<T> y;

  Vector2<T> normalize();
  Vector2<T> normalized() const;

  template <class U>
  Vector2<T>& operator=(const Vector2<U>& other);

protected:
  static const uint32_t m_xIndex = 0;
  static const uint32_t m_yIndex = 1;
};

template <class T>
Vector2<T>::Vector2()
    : VectorBase<T, 2>()
    , x(&VectorBase<T, 2>::m_values[m_xIndex])
    , y(&VectorBase<T, 2>::m_values[m_yIndex]) {
  setValue(m_xIndex, 0);
  setValue(m_yIndex, 0);
}

template <class T>
Vector2<T>::Vector2(const T& x_, const T& y_)
    : VectorBase<T, 2>()
    , x(&VectorBase<T, 2>::m_values[m_xIndex])
    , y(&VectorBase<T, 2>::m_values[m_yIndex]) {
  setValue(m_xIndex, x_);
  setValue(m_yIndex, y_);
}

template <class T>
Vector2<T>::Vector2(const VectorBase<T, 2>& vector)
    : VectorBase<T, 2>(vector)
    , x(&VectorBase<T, 2>::m_values[m_xIndex])
    , y(&VectorBase<T, 2>::m_values[m_yIndex]) {}

template <class T>
Vector2<T>::Vector2(const Vector2<T>& vector)
    : VectorBase<T, 2>(vector)
    , x(&VectorBase<T, 2>::m_values[m_xIndex])
    , y(&VectorBase<T, 2>::m_values[m_yIndex]) {}

template <class T>
Vector2<T>::~Vector2() {}

template <class T>
T Vector2<T>::getValue(uint32_t index) const {
  try {
    return VectorBase<T, 2>::getValue(index);
  } catch(std::exception& e) {
    LOG_ERROR(e.what());
    return 0;
  }
}

template <class T>
void Vector2<T>::setValue(uint32_t index, const T& value) {
  try {
    VectorBase<T, 2>::setValue(index, value);
  } catch(std::exception& e) {
    LOG_ERROR(e.what());
  }
}

template <class T>
T Vector2<T>::operator[](const uint32_t index) {
  try {
    return VectorBase<T, 2>::getValue(index);
  } catch(std::exception& e) {
    LOG_ERROR(e.what());
    return 0;
  }
}

template <class T>
Vector2<T> Vector2<T>::normalize() {
  return VectorBase<T, 2>::normalize();
}

template <class T>
Vector2<T> Vector2<T>::normalized() const {
  return VectorBase<T, 2>::normalized();
}

template <class T>
template <class U>
Vector2<T>& Vector2<T>::operator=(const Vector2<U>& other) {
  this->assign(other);
  x = Property<T>(&VectorBase<T, 2>::m_values[m_xIndex]);
  y = Property<T>(&VectorBase<T, 2>::m_values[m_yIndex]);
}

using Vec2f = Vector2<float>;
using Vec2i = Vector2<int>;