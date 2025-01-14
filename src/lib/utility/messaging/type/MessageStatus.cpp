// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "MessageStatus.hpp"

#include "utilityString.h"

MessageStatus::MessageStatus(const std::wstring& status, bool isError, bool showLoader, bool showInStatusBar)
    : isError(isError), showLoader(showLoader), showInStatusBar(showInStatusBar) {
  m_stati.push_back(utility::replace(status, L"\n", L" "));

  setSendAsTask(false);
}

MessageStatus::MessageStatus(std::vector<std::wstring> stati, bool isError, bool showLoader,
                             bool showInStatusBar)
    : isError(isError), showLoader(showLoader), showInStatusBar(showInStatusBar), m_stati(std::move(stati)) {
  setSendAsTask(false);
}

std::string MessageStatus::getStaticType() { return "MessageStatus"; }

const std::vector<std::wstring>& MessageStatus::stati() const { return m_stati; }

std::wstring MessageStatus::status() const {
  if (!m_stati.empty()) {
    return m_stati[0];
  }

  return {};
}

void MessageStatus::print(std::wostream& outStream) const {
  for (const std::wstring& status : m_stati) {
    outStream << status;

    if (m_stati.size() > 1) {
      outStream << L" - ";
    }
  }

  if (isError) {
    outStream << L" - error";
  }

  if (showLoader) {
    outStream << L" - loading";
  }
}
