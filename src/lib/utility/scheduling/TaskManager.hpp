#pragma once

#include <memory>

#include "types.hpp"

class TaskScheduler;

namespace taskManager {

std::shared_ptr<TaskScheduler> createScheduler(Id schedulerId);

void destroyScheduler(Id schedulerId);

std::shared_ptr<TaskScheduler> getScheduler(Id schedulerId);

}  // namespace taskManager
