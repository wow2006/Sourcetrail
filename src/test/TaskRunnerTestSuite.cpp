// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <cstddef>
#include <memory>

#include "catch.hpp"
#include "trompeloeil.hpp"

#include "TaskRunner.hpp"
#include "Blackboard.hpp"

using trompeloeil::_;

class MockedTask : public Task {
    MAKE_MOCK1(doEnter, void(std::shared_ptr<Blackboard>), override);
    MAKE_MOCK1(doUpdate, Task::TaskState(std::shared_ptr<Blackboard>), override);
    MAKE_MOCK1(doExit, void(std::shared_ptr<Blackboard>), override);
    MAKE_MOCK1(doReset, void(std::shared_ptr<Blackboard>), override);

    MAKE_MOCK0(terminate, void(), override);
};

TEST_CASE("TaskRunner", "[lib]") {
    auto mockedTask = std::make_shared<MockedTask>();

    SECTION("update taskID") {
        ALLOW_CALL(*mockedTask, doEnter(_));
        ALLOW_CALL(*mockedTask, doUpdate(_))
            .RETURN(Task::TaskState::STATE_SUCCESS);
        ALLOW_CALL(*mockedTask, doExit(_));

        TaskRunner runner(mockedTask);
        REQUIRE(Task::TaskState::STATE_SUCCESS == runner.update(0));
    }

    SECTION("update taskID reset") {
        ALLOW_CALL(*mockedTask, doReset(_));    
        ALLOW_CALL(*mockedTask, doEnter(_));
        ALLOW_CALL(*mockedTask, doUpdate(_))
            .RETURN(Task::TaskState::STATE_SUCCESS);
        ALLOW_CALL(*mockedTask, doExit(_));

        TaskRunner runner(mockedTask);
        runner.reset();
        REQUIRE(Task::TaskState::STATE_SUCCESS == runner.update(0));
    }

    SECTION("update Blackboard") {
        auto fakeBlackboard = std::make_shared<Blackboard>();

        ALLOW_CALL(*mockedTask, doEnter(fakeBlackboard));
        ALLOW_CALL(*mockedTask, doUpdate(fakeBlackboard))
            .RETURN(Task::TaskState::STATE_SUCCESS);
        ALLOW_CALL(*mockedTask, doExit(fakeBlackboard));

        TaskRunner runner(mockedTask);
        REQUIRE(Task::TaskState::STATE_SUCCESS == runner.update(fakeBlackboard));
    }

    SECTION("update Blackboard reset") {
        auto fakeBlackboard = std::make_shared<Blackboard>();

        ALLOW_CALL(*mockedTask, doReset(fakeBlackboard));    
        ALLOW_CALL(*mockedTask, doEnter(fakeBlackboard));
        ALLOW_CALL(*mockedTask, doUpdate(fakeBlackboard))
            .RETURN(Task::TaskState::STATE_SUCCESS);
        ALLOW_CALL(*mockedTask, doExit(fakeBlackboard));

        TaskRunner runner(mockedTask);
        runner.reset();
        REQUIRE(Task::TaskState::STATE_SUCCESS == runner.update(fakeBlackboard));
    }

    SECTION("terminate") {
        REQUIRE_CALL(*mockedTask, terminate());

        TaskRunner runner(mockedTask);
        runner.terminate();
    }
}

