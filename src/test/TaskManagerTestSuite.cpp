// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "catch.hpp"
#include "TaskManager.hpp"

TEST_CASE("TaskManager", "[lib]") {
  constexpr auto taskId = 20;
  auto task = taskManager::createScheduler(taskId);
  SECTION("Create") {
    REQUIRE(task);
  }

  SECTION("Get") {
    auto taskExists = taskManager::getScheduler(taskId);
    REQUIRE(taskExists == task);
  }

  SECTION("Remove") {
    taskManager::destroyScheduler(taskId);
    auto newTask = taskManager::getScheduler(taskId);
    REQUIRE_FALSE(newTask == task);
  }
}

