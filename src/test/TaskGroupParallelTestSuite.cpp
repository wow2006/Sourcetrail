// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "catch.hpp"
#include "trompeloeil.hpp"

#include "TaskGroupParallel.hpp"

using trompeloeil::_;

class MockedTask : public Task {
    MAKE_MOCK1(doEnter, void(std::shared_ptr<Blackboard>), override);
    MAKE_MOCK1(doUpdate, Task::TaskState(std::shared_ptr<Blackboard>), override);
    MAKE_MOCK1(doExit, void(std::shared_ptr<Blackboard>), override);
    MAKE_MOCK1(doReset, void(std::shared_ptr<Blackboard>), override);

    MAKE_MOCK0(terminate, void(), override);
};

TEST_CASE("TaskGroupParallel", "[lib]") {
  auto mockedTask = std::make_shared<MockedTask>();

  /*
  ALLOW_CALL(*mockedTask, doEnter(_));
  ALLOW_CALL(*mockedTask, doUpdate(_))
      .RETURN(Task::TaskState::STATE_SUCCESS);
  ALLOW_CALL(*mockedTask, doExit(_));
  */

  TaskGroupParallel taskGroup;
  taskGroup.addTask(mockedTask);
}

