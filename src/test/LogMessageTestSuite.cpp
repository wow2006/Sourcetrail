// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <ctime>
#include <thread>

#include "catch.hpp"

#include "LogMessage.hpp"

TEST_CASE("LogMessageTestSuite", "[lib]") {
  constexpr uint32_t line = 10;
  std::tm time{};
  LogMessage message(L"Help", "something.cpp", "func", line, time, std::this_thread::get_id());
}
