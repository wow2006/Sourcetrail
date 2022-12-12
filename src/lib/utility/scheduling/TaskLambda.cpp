// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TaskLambda.hpp"

TaskLambda::TaskLambda(std::function<void()> func) : m_func(std::move(func)) {}

void TaskLambda::doEnter([[maybe_unused]] std::shared_ptr<Blackboard> blackboard) {}

Task::TaskState TaskLambda::doUpdate([[maybe_unused]] std::shared_ptr<Blackboard> blackboard) {
  m_func();
  return STATE_SUCCESS;
}

void TaskLambda::doExit([[maybe_unused]] std::shared_ptr<Blackboard> blackboard) {}

void TaskLambda::doReset([[maybe_unused]] std::shared_ptr<Blackboard> blackboard) {}
