#pragma once

#include <string>

namespace clang {
namespace tooling {
class CompilationDatabase;
}
}  // namespace clang

struct ClangInvocationInfo {
  static ClangInvocationInfo getClangInvocationString(const clang::tooling::CompilationDatabase* compilationDatabase);

  std::string invocation;
  std::string errors;
};
