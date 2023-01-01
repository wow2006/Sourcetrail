#include "TaskGroupSelector.h"

TaskGroupSelector::TaskGroupSelector(): m_taskIndex(0) {}

void TaskGroupSelector::addTask(std::shared_ptr<Task> task) {
  m_taskRunners.push_back(std::make_shared<TaskRunner>(task));
}

void TaskGroupSelector::doEnter(std::shared_ptr<Blackboard> /*blackboard*/) {
  m_taskIndex = 0;
}

Task::TaskState TaskGroupSelector::doUpdate(std::shared_ptr<Blackboard> blackboard) {
  if(m_taskIndex >= static_cast<int>(m_taskRunners.size())) {
    return STATE_FAILURE;
  }

  TaskState state = m_taskRunners[m_taskIndex]->update(blackboard);

  if(state == STATE_FAILURE) {
    m_taskIndex++;

    if(m_taskIndex >= int(m_taskRunners.size())) {
      return STATE_FAILURE;
    }
  } else if(state == STATE_SUCCESS) {
    return STATE_SUCCESS;
  } else if(state == STATE_HOLD) {
    return STATE_HOLD;
  }

  return STATE_RUNNING;
}

void TaskGroupSelector::doExit(std::shared_ptr<Blackboard> /*blackboard*/) {}

void TaskGroupSelector::doReset(std::shared_ptr<Blackboard> /*blackboard*/) {
  for(auto& m_taskRunner : m_taskRunners) {
    m_taskRunner->reset();
  }
}

void TaskGroupSelector::doTerminate() {
  for(auto& m_taskRunner : m_taskRunners) {
    m_taskRunner->terminate();
  }
}
