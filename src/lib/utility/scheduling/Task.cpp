// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Task.hpp"

#include "TaskManager.hpp"
#include "TaskScheduler.hpp"

Task::~Task() noexcept = default;

void Task::dispatch(Id schedulerId, std::shared_ptr<Task> task) {
  taskManager::getScheduler(schedulerId)->pushTask(std::move(task));
}

void Task::dispatchNext(Id schedulerId, std::shared_ptr<Task> task) {
  taskManager::getScheduler(schedulerId)->pushNextTask(std::move(task));
}

void Task::setIsBackgroundTask(bool background) { m_isBackgroundTask = background; }

Task::TaskState Task::update(std::shared_ptr<Blackboard> blackboard) {
  if (!m_enterCalled) {
    doEnter(blackboard);
    m_enterCalled = true;
  }

  TaskState state = doUpdate(blackboard);

  if (m_isBackgroundTask && state == STATE_RUNNING) {
    state = STATE_HOLD;
  }

  if ((state == STATE_SUCCESS || state == STATE_FAILURE) && !m_exitCalled) {
    doExit(blackboard);
    m_exitCalled = true;
  }

  return state;
}

void Task::reset(std::shared_ptr<Blackboard> blackboard) {
  doReset(blackboard);
  m_enterCalled = false;
  m_exitCalled = false;
}

void Task::terminate() {}
