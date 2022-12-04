#pragma once

#include <clang/AST/Decl.h>

class CxxContext {
 public:
  virtual ~CxxContext() = default;
  virtual const clang::NamedDecl* getDecl() const;
  virtual const clang::Type* getType() const;
};

class CxxContextDecl : public CxxContext {
 public:
  explicit CxxContextDecl(const clang::NamedDecl* decl);
  const clang::NamedDecl* getDecl() const override;

 private:
  const clang::NamedDecl* m_decl;
};

class CxxContextType : public CxxContext {
 public:
  CxxContextType(const clang::Type* type);
  const clang::Type* getType() const override;

 private:
  const clang::Type* m_type;
};
