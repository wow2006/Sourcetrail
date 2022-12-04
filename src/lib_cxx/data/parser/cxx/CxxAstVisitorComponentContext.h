#pragma once

#include "CxxAstVisitorComponent.h"
#include "CxxContext.h"

// This CxxAstVisitorComponent is responsible for recording and providing the decl/type that acts as
// the context of the currently traversed/visited node. Example: void foo() { bar(); } For this
// snippet the declaration of "foo" serves as the context of the call to "bar"
class CxxAstVisitorComponentContext : public CxxAstVisitorComponent {
 public:
  explicit CxxAstVisitorComponentContext(CxxAstVisitor* astVisitor);

  const clang::NamedDecl* getTopmostContextDecl(const size_t skip = 0) const;
  const CxxContext* getContext(const size_t skip = 0) const;

  void beginTraverseDecl(clang::Decl* d);
  void endTraverseDecl(clang::Decl* d);

  void beginTraverseTypeLoc(const clang::TypeLoc& tl);
  void endTraverseTypeLoc(const clang::TypeLoc& tl);

  void beginTraverseLambdaExpr(clang::LambdaExpr* s);
  void endTraverseLambdaExpr(clang::LambdaExpr* s);

  void beginTraverseFunctionDecl(clang::FunctionDecl* d);
  void endTraverseFunctionDecl(clang::FunctionDecl* d);

  void beginTraverseClassTemplateSpecializationDecl(clang::ClassTemplateSpecializationDecl* d);
  void endTraverseClassTemplateSpecializationDecl(clang::ClassTemplateSpecializationDecl* d);

  void beginTraverseClassTemplatePartialSpecializationDecl(clang::ClassTemplatePartialSpecializationDecl* d);
  void endTraverseClassTemplatePartialSpecializationDecl(clang::ClassTemplatePartialSpecializationDecl* d);

  void beginTraverseDeclRefExpr(clang::DeclRefExpr* s);
  void endTraverseDeclRefExpr(clang::DeclRefExpr* s);

  void beginTraverseTemplateSpecializationTypeLoc(const clang::TemplateSpecializationTypeLoc& loc);
  void endTraverseTemplateSpecializationTypeLoc(const clang::TemplateSpecializationTypeLoc& loc);

  void beginTraverseUnresolvedLookupExpr(clang::UnresolvedLookupExpr* e);
  void endTraverseUnresolvedLookupExpr(clang::UnresolvedLookupExpr* e);

  void beginTraverseTemplateArgumentLoc(const clang::TemplateArgumentLoc& loc);
  void endTraverseTemplateArgumentLoc(const clang::TemplateArgumentLoc& loc);

 private:
  std::vector<std::shared_ptr<CxxContext>> m_contextStack;
  std::vector<std::shared_ptr<CxxContext>> m_templateArgumentContext;
};
