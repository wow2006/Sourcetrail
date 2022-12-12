// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <memory>

#include "catch.hpp"

#include "TaskLambda.hpp"
#include "Blackboard.hpp"

TEST_CASE("MessageQueue", "[utility]") {
    bool bCalled = false;
    auto blackboard = std::make_shared<Blackboard>();

    TaskLambda task([&bCalled]() { bCalled = true; });
    task.update(blackboard);

    REQUIRE(bCalled);    
}
