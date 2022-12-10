#pragma once

template <class T>
class Property final {
 public:
  explicit Property(T* valuePointer) noexcept;

  Property(const Property&) = delete;

  Property(Property&&) = delete;

  Property& operator=(const Property& property);

  Property& operator=(Property&&) = delete;

  ~Property() = default;

  [[nodiscard]] T& operator=(const T& value);

  operator const T&() const;  // NOLINT(hicpp-explicit-conversions)

  T& operator()() const;

 private:
  T* m_valuePointer;
};

template <class T>
Property<T>::Property(T* valuePointer) noexcept : m_valuePointer(valuePointer) {}

template <class T>
T& Property<T>::operator=(const T& value) {
  *m_valuePointer = value;
  return *m_valuePointer;
}

template <class T>
Property<T>& Property<T>::operator=(const Property<T>& property) {
  return *this;
}

template <class T>
Property<T>::operator const T&() const {
  return *m_valuePointer;
}

template <class T>
T& Property<T>::operator()() const {
  return *m_valuePointer;
}
