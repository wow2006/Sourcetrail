#pragma once

#include "FilePath.h"
#include "utilityString.h"

namespace utility {

template <typename T>
std::vector<std::vector<T>> splitToEquallySizedParts(const std::vector<T>& values,
                                                     size_t desiredPartCount);

template <typename T>
std::vector<T> concat(const std::vector<T>& a, const std::vector<T>& b);

template <typename T>
std::set<T> concat(const std::set<T>& a, const std::set<T>& b);

template <typename T>
std::vector<T> concat(const std::vector<T>& a, const T& b);

template <typename T>
std::set<T> concat(const std::set<T>& a, const T& b);

template <typename T>
void append(std::vector<T>& a, const std::vector<T>& b);

template <typename T>
void append(std::set<T>& a, const std::set<T>& b);

template <typename T>
void append(std::unordered_set<T>& a, const std::unordered_set<T>& b);

template <typename T>
std::vector<T> unique(const std::vector<T>& a);

template <typename T>
std::vector<T> toVector(const std::deque<T>& d);

template <typename T>
std::vector<T> toVector(const std::set<T>& d);

template <typename T>
std::vector<T> toVector(const std::list<T>& d);

template <typename T>
std::set<T> toSet(const std::vector<T>& d);

template <typename T>
void fillVectorWithElements(std::vector<T>& v, const T& arg);

template <typename T, typename... Args>
void fillVectorWithElements(std::vector<T>& v, const T& arg, const Args&... args);

template <typename T, typename... Args>
std::vector<T> createVectorFromElements(const Args&... args);

template <typename SourceType, typename TargetType>
std::vector<TargetType> convert(const std::vector<SourceType>& sourceContainer,
                                std::function<TargetType(const SourceType&)> conversion);

template <typename SourceType, typename TargetType>
std::vector<TargetType> convert(const std::vector<SourceType>& sourceContainer);

template <typename SourceType, typename TargetType>
std::set<TargetType> convert(const std::set<SourceType>& sourceContainer,
                             std::function<TargetType(const SourceType&)> conversion);

template <typename SourceType, typename TargetType>
std::set<TargetType> convert(const std::set<SourceType>& sourceContainer);

template <typename T>
std::vector<std::string> toStrings(const std::vector<T>& d);
template <>
std::vector<std::string> toStrings(const std::vector<FilePath>& d);

template <typename T>
std::vector<std::wstring> toWStrings(const std::vector<T>& d);
template <>
std::vector<std::wstring> toWStrings(const std::vector<FilePath>& d);

template <typename T>
bool isPermutation(const std::vector<T>& a, const std::vector<T>& b) {
  return (a.size() == b.size() && std::is_permutation(a.begin(), a.end(), b.begin()));
}

template <typename T>
bool containsElement(const std::vector<T>& v, const T& e) {
  for(const T& ve: v) {
    if(ve == e) {
      return true;
    }
  }
  return false;
}

template <typename T>
bool shareElement(const std::set<T>& a, const std::set<T>& b) {
  const std::set<T>* aPtr = a.size() > b.size() ? &a : &b;
  const std::set<T>* bPtr = aPtr == &a ? &b : &a;

  for(const T& bt: *bPtr) {
    if(aPtr->find(bt) != aPtr->end()) {
      return true;
    }
  }

  return false;
}

size_t digits(size_t n);

}    // namespace utility

#include "utility_impl.h"