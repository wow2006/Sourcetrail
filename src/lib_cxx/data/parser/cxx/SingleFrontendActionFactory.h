#pragma once

#include <clang/Tooling/Tooling.h>

class SingleFrontendActionFactory : public clang::tooling::FrontendActionFactory {
 public:
  explicit SingleFrontendActionFactory(clang::FrontendAction* action);

  std::unique_ptr<clang::FrontendAction> create() override;

 private:
  clang::FrontendAction* m_action;
};