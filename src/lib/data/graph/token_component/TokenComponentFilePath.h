#pragma once

#include "FilePath.h"
#include "TokenComponent.h"

class TokenComponentFilePath : public TokenComponent {
public:
  TokenComponentFilePath(const utility::file::FilePath& path, bool complete);
  ~TokenComponentFilePath() override;

  virtual std::shared_ptr<TokenComponent> copy() const;

  const utility::file::FilePath& getFilePath() const;
  bool isComplete() const;

private:
  const utility::file::FilePath m_path;
  const bool m_complete;
};