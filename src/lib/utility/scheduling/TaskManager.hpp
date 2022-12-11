#pragma once

#include <map>
#include <memory>
#include <mutex>

#include "types.hpp"

class TaskScheduler;

class TaskManager {
 public:
  static std::shared_ptr<TaskScheduler> createScheduler(Id schedulerId);
  static void destroyScheduler(Id schedulerId);

  static std::shared_ptr<TaskScheduler> getScheduler(Id schedulerId);

 private:
  static std::map<Id, std::shared_ptr<TaskScheduler>> s_schedulers;
  static std::mutex s_schedulersMutex;
};
