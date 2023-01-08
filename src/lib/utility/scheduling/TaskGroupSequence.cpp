#include "TaskGroupSequence.h"

TaskGroupSequence::TaskGroupSequence() = default;

void TaskGroupSequence::addTask(std::shared_ptr<Task> task) {
  m_taskRunners.push_back(std::make_shared<TaskRunner>(task));
}

void TaskGroupSequence::doEnter(std::shared_ptr<Blackboard> /*blackboard*/) {
  m_taskIndex = 0;
}

Task::TaskState TaskGroupSequence::doUpdate(std::shared_ptr<Blackboard> blackboard) {
  if(m_taskIndex >= static_cast<int>(m_taskRunners.size())) {
    return STATE_SUCCESS;
  }
  if(m_taskIndex < 0) {
    return STATE_FAILURE;
  }

  TaskState state = m_taskRunners[m_taskIndex]->update(blackboard);

  if(state == STATE_SUCCESS) {
    m_taskIndex++;
  } else if(state == STATE_FAILURE) {
    m_taskIndex = -1;
  } else if(state == STATE_HOLD) {
    return STATE_HOLD;
  }

  return STATE_RUNNING;
}

void TaskGroupSequence::doExit(std::shared_ptr<Blackboard> /*blackboard*/) {}

void TaskGroupSequence::doReset(std::shared_ptr<Blackboard> /*blackboard*/) {
  for(auto& m_taskRunner: m_taskRunners) {
    m_taskRunner->reset();
  }
}

void TaskGroupSequence::doTerminate() {
  for(auto& m_taskRunner: m_taskRunners) {
    m_taskRunner->terminate();
  }
}
