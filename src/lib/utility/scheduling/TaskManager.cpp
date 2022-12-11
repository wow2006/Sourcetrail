// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TaskManager.hpp"

#include <map>
#include <mutex>

#include "TaskScheduler.hpp"

std::map<Id, std::shared_ptr<TaskScheduler>> s_schedulers;

std::mutex s_schedulersMutex;

namespace taskManager {

std::shared_ptr<TaskScheduler> createScheduler(Id schedulerId) { return getScheduler(schedulerId); }

void destroyScheduler(Id schedulerId) {
  std::lock_guard<std::mutex> lock(s_schedulersMutex);

  auto it = s_schedulers.find(schedulerId);
  if (it != s_schedulers.end()) {
    s_schedulers.erase(it);
  }
}

std::shared_ptr<TaskScheduler> getScheduler(Id schedulerId) {
  std::lock_guard<std::mutex> lock(s_schedulersMutex);

  auto it = s_schedulers.find(schedulerId);
  if (it != s_schedulers.end()) {
    return it->second;
  }

  auto scheduler = std::make_shared<TaskScheduler>(schedulerId);
  s_schedulers.emplace(schedulerId, scheduler);
  return scheduler;
}

}  // namespace taskManager