// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TaskLambda.hpp"

TaskLambda::TaskLambda(std::function<void()> func) : m_func(func) {}

void TaskLambda::doEnter(std::shared_ptr<Blackboard> blackboard) {}

Task::TaskState TaskLambda::doUpdate(std::shared_ptr<Blackboard> blackboard) {
  m_func();
  return STATE_SUCCESS;
}

void TaskLambda::doExit(std::shared_ptr<Blackboard> blackboard) {}

void TaskLambda::doReset(std::shared_ptr<Blackboard> blackboard) {}
