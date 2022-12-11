#pragma once

#include <string>
#include <vector>

#include "Message.h"

class MessageStatus final : public Message<MessageStatus> {
 public:
  explicit MessageStatus(const std::wstring& status, bool isError = false, bool showLoader = false, bool showInStatusBar = true);

  explicit MessageStatus(std::vector<std::wstring> stati, bool isError = false, bool showLoader = false,
                bool showInStatusBar = true);

  static std::string getStaticType();

  [[nodiscard]] const std::vector<std::wstring>& stati() const;

  [[nodiscard]] std::wstring status() const;

  void print(std::wostream& outStream) const override;

  const bool isError;
  const bool showLoader;
  const bool showInStatusBar;

 private:
  std::vector<std::wstring> m_stati;
};
