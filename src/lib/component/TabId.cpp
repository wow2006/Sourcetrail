// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TabId.hpp"

Id TabId::s_nextTabId = 10;
Id TabId::s_currentTabId = 0;

Id TabId::app() { return 1; }

Id TabId::background() { return 2; }

Id TabId::ignore() { return 3; }

Id TabId::nextTab() { return s_nextTabId++; }

Id TabId::currentTab() { return s_currentTabId; }

void TabId::setCurrentTabId(Id currentTabId) { s_currentTabId = currentTabId; }
