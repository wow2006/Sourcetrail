#include "MessageBase.h"

#include "utilityString.h"


Id MessageBase::s_nextId = 1;

MessageBase::MessageBase()
    : m_id(s_nextId++)
    , m_schedulerId(0)
    , m_isParallel(false)
    , m_isReplayed(false)
    , m_sendAsTask(true)
    , m_keepContent(false)
    , m_isLast(true)
    , m_isLogged(true) {}

MessageBase::~MessageBase() = default;

std::wstring MessageBase::str() const {
  std::wstringstream ss;
  ss << utility::decodeFromUtf8(getType()) << L" ";
  print(ss);
  return ss.str();
}