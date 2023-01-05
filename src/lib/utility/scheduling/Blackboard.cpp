#include "Blackboard.h"

BlackboardItemBase::~BlackboardItemBase() = default;

Blackboard::Blackboard() = default;

Blackboard::Blackboard(std::shared_ptr<Blackboard> parent): m_parent(std::move(parent)) {}

bool Blackboard::exists(const std::string& key) {
  std::lock_guard<std::mutex> lock(m_itemMutex);

  auto itr = m_items.find(key);
  return (itr != m_items.end());
}

bool Blackboard::clear(const std::string& key) {
  std::lock_guard<std::mutex> lock(m_itemMutex);

  auto itr = m_items.find(key);
  if(itr != m_items.end()) {
    m_items.erase(itr);
    return true;
  }
  return false;
}
