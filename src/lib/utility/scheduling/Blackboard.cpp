// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Blackboard.hpp"

Blackboard::Blackboard() noexcept = default;

Blackboard::Blackboard(std::shared_ptr<Blackboard> parent) noexcept : m_parent(std::move(parent)) {}

bool Blackboard::exists(const std::string& key) {
  std::lock_guard<std::mutex> lock(m_itemMutex);

  auto itr = m_items.find(key);
  return (itr != m_items.end());
}

bool Blackboard::clear(const std::string& key) {
  std::lock_guard<std::mutex> lock(m_itemMutex);

  auto itr = m_items.find(key);
  if (itr != m_items.end()) {
    m_items.erase(itr);
    return true;
  }
  return false;
}
