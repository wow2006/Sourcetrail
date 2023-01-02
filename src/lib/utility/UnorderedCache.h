#pragma once

namespace utility {

template <typename KeyType, typename ValType, typename Hasher = std::hash<KeyType>>
class UnorderedCache {
public:
  explicit UnorderedCache(std::function<ValType(const KeyType&)> calculator);

  ValType getValue(const KeyType& key);

private:
  std::function<ValType(const KeyType&)> m_calculator;

  std::unordered_map<KeyType, ValType, Hasher> m_map;

  size_t m_hitCount = {};
  size_t m_missCount = {};
};

template <typename KeyType, typename ValType, typename Hasher>
UnorderedCache<KeyType, ValType, Hasher>::UnorderedCache(std::function<ValType(const KeyType&)> calculator)
    : m_calculator(std::move(calculator)) {}

template <typename KeyType, typename ValType, typename Hasher>
ValType UnorderedCache<KeyType, ValType, Hasher>::getValue(const KeyType& key) {
  auto itr = m_map.find(key);
  if(itr != m_map.cend()) {
    ++m_hitCount;
    return itr->second;
  }

  ++m_missCount;
  ValType val = m_calculator(key);
  m_map.emplace(key, std::forward<ValType>(val));
  return val;
}

} // namespace utility
