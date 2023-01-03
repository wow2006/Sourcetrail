#pragma once

#include "Property.h"
#include "logging.h"

#include "VectorBase.h"

template <class T>
class Vector4 : public VectorBase<T, 4> {
public:
  Vector4();
  Vector4(const T& x_, const T& y_, const T& z_, const T& w_);
  Vector4(const VectorBase<T, 4>& vector);
  Vector4(const Vector4<T>& vector);
  virtual ~Vector4();

  T getValue(uint32_t index) const;
  void setValue(uint32_t index, const T& value);

  T& operator[](uint32_t index);

  Property<T> x;
  Property<T> y;
  Property<T> z;
  Property<T> w;

  Vector4<T> normalize();
  Vector4<T> normalized() const;

  template <class U>
  Vector4<T>& operator=(const Vector4<U>& other);

protected:
  static const uint32_t m_xIndex = 0;
  static const uint32_t m_yIndex = 1;
  static const uint32_t m_zIndex = 2;
  static const uint32_t m_wIndex = 3;
};

template <class T>
Vector4<T>::Vector4()
    : VectorBase<T, 4>()
    , x(&VectorBase<T, 4>::m_values[m_xIndex])
    , y(&VectorBase<T, 4>::m_values[m_yIndex])
    , z(&VectorBase<T, 4>::m_values[m_zIndex])
    , w(&VectorBase<T, 4>::m_values[m_wIndex]) {
  setValue(m_xIndex, 0);
  setValue(m_yIndex, 0);
  setValue(m_zIndex, 0);
  setValue(m_wIndex, 0);
}

template <class T>
Vector4<T>::Vector4(const T& x_, const T& y_, const T& z_, const T& w_)
    : VectorBase<T, 4>()
    , x(&VectorBase<T, 4>::m_values[m_xIndex])
    , y(&VectorBase<T, 4>::m_values[m_yIndex])
    , z(&VectorBase<T, 4>::m_values[m_zIndex])
    , w(&VectorBase<T, 4>::m_values[m_wIndex]) {
  setValue(m_xIndex, x_);
  setValue(m_yIndex, y_);
  setValue(m_zIndex, z_);
  setValue(m_wIndex, w_);
}

template <class T>
Vector4<T>::Vector4(const VectorBase<T, 4>& vector)
    : VectorBase<T, 4>(vector)
    , x(&VectorBase<T, 4>::m_values[m_xIndex])
    , y(&VectorBase<T, 4>::m_values[m_yIndex])
    , z(&VectorBase<T, 4>::m_values[m_zIndex])
    , w(&VectorBase<T, 4>::m_values[m_wIndex]) {}

template <class T>
Vector4<T>::Vector4(const Vector4<T>& vector)
    : VectorBase<T, 4>(vector)
    , x(&VectorBase<T, 4>::m_values[m_xIndex])
    , y(&VectorBase<T, 4>::m_values[m_yIndex])
    , z(&VectorBase<T, 4>::m_values[m_zIndex])
    , w(&VectorBase<T, 4>::m_values[m_wIndex]) {}

template <class T>
Vector4<T>::~Vector4() {}

template <class T>
T Vector4<T>::getValue(uint32_t index) const {
  try {
    return VectorBase<T, 4>::getValue(index);
  } catch(std::exception& e) {
    LOG_ERROR(e.what());
    return 0;
  }
}

template <class T>
void Vector4<T>::setValue(uint32_t index, const T& value) {
  try {
    VectorBase<T, 4>::setValue(index, value);
  } catch(std::exception& e) {
    LOG_ERROR(e.what());
  }
}

template <class T>
T& Vector4<T>::operator[](uint32_t index) {
  try {
    return VectorBase<T, 4>::getValue(index);
  } catch(std::exception& e) {
    LOG_ERROR(e.what());
    return 0;
  }
}

template <class T>
Vector4<T> Vector4<T>::normalize() {
  return VectorBase<T, 4>::normalize();
}

template <class T>
Vector4<T> Vector4<T>::normalized() const {
  return VectorBase<T, 4>::normalized();
}

template <class T>
template <class U>
Vector4<T>& Vector4<T>::operator=(const Vector4<U>& other) {
  this->assign(other);
}

using Vec4f = Vector4<float>;
using Vec4i = Vector4<int>;