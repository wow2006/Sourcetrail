#pragma once

#include "types.h"

class TabId {
 public:
  static Id app();
  static Id background();
  static Id ignore();

  static Id nextTab();
  static Id currentTab();

  static void setCurrentTabId(Id currentTabId);

 private:
  static Id s_nextTabId;
  static Id s_currentTabId;
};
