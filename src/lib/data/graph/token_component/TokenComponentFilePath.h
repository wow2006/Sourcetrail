#pragma once

#include "FilePath.h"

#include "TokenComponent.h"

class TokenComponentFilePath : public TokenComponent {
public:
  TokenComponentFilePath(const FilePath& path, bool complete);
  ~TokenComponentFilePath() override;

  virtual std::shared_ptr<TokenComponent> copy() const;

  const FilePath& getFilePath() const;
  bool isComplete() const;

private:
  const FilePath m_path;
  const bool m_complete;
};