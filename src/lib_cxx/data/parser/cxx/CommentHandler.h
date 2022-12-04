#pragma once

#include <clang/Lex/Preprocessor.h>

class CanonicalFilePathCache;
class ParserClient;

class CommentHandler : public clang::CommentHandler {
 public:
  CommentHandler(std::shared_ptr<ParserClient> client, std::shared_ptr<CanonicalFilePathCache> canonicalFilePathCache);

  virtual ~CommentHandler() = default;

  virtual bool HandleComment(clang::Preprocessor& preprocessor, clang::SourceRange sourceRange) override;

 private:
  std::shared_ptr<ParserClient> m_client;
  std::shared_ptr<CanonicalFilePathCache> m_canonicalFilePathCache;
};
