#pragma once

#include <vector>

#include "CxxAstVisitorComponent.h"
#include "ReferenceKind.h"

// This CxxAstVisitorComponent is responsible for recording and providing the context based
// ReferenceKind for each reference to a type encountered while traversing the AST. Example: class
// Foo: public Bar {}; For this snippet the type "Bar" is used in the context of an inheritance.
class CxxAstVisitorComponentTypeRefKind : public CxxAstVisitorComponent {
 public:
  explicit CxxAstVisitorComponentTypeRefKind(CxxAstVisitor* astVisitor);

  bool isTraversingInheritance() const;
  bool isTraversingTemplateArgument() const;

  void beginTraverseCXXBaseSpecifier();
  void endTraverseCXXBaseSpecifier();

  void beginTraverseTemplateDefaultArgumentLoc();
  void endTraverseTemplateDefaultArgumentLoc();

  void beginTraverseTemplateArgumentLoc(const clang::TemplateArgumentLoc& loc);
  void endTraverseTemplateArgumentLoc(const clang::TemplateArgumentLoc& loc);

 private:
  enum StateKind { STATE_USAGE, STATE_INHERITANCE, STATE_TEMPLATE_ARGUMENT };

  std::vector<StateKind> m_stateKindStack;
};
