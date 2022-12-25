#pragma once

#include <algorithm>   // for copy, max, copy, find_if_not, transform
#include <cstddef>     // for size_t
#include <type_traits> //
#include <deque>       // for deque, operator!=
#include <sstream>     // for basic_ostream, stringstream, wstringstream
#include <string>      // for string, wstring, operator<<
#include <utility>     // for pair
#include <vector>      // for vector

namespace utility {

/**
 * @name encode/decode Utf8
 * @{ */
std::string encodeToUtf8(std::wstring input);

std::wstring decodeFromUtf8(std::string input);
/**  @} */

/**
 * @name split string
 * @{ */
template<class ContainerType, class StringType>
ContainerType split(const StringType& str, const StringType& delimiter);

std::deque<std::string> split(std::string str, char delimiter);

std::deque<std::string> split(std::string str, std::string delimiter);

std::vector<std::string> splitToVector(std::string str, char delimiter);

std::vector<std::string> splitToVector(std::string str, std::string delimiter);

std::vector<std::wstring> splitToVector(std::wstring str, wchar_t delimiter);

std::vector<std::wstring> splitToVector(std::wstring str, std::wstring delimiter);
/**  @} */

/**
 * @name join string
 * @{ */
template <typename ContainerType, class StringType>
StringType join(const ContainerType& list, const StringType& delimiter);

std::string join(const std::deque<std::string>& list, char delimiter);

std::string join(const std::deque<std::string>& list, const std::string& delimiter);

std::string join(const std::vector<std::string>& list, char delimiter);

std::string join(const std::vector<std::string>& list, const std::string& delimiter);
/**  @} */

std::deque<std::string> tokenize(const std::string& str, char delimiter);
std::deque<std::string> tokenize(const std::string& str, const std::string& delimiter);
std::deque<std::string> tokenize(const std::deque<std::string>& list, char delimiter);
std::deque<std::string> tokenize(const std::deque<std::string>& list, const std::string& delimiter);

std::string substrBeforeFirst(const std::string& str, char delimiter);
std::string substrBeforeFirst(const std::string& str, const std::string& delimiter);
std::string substrBeforeLast(const std::string& str, char delimiter);
std::wstring substrBeforeLast(const std::wstring& str, wchar_t delimiter);
std::wstring substrAfterLast(const std::wstring& str, wchar_t delimiter);
std::string substrAfter(const std::string& str, char delimiter);
std::string substrAfter(const std::string& str, const std::string& delimiter);

template <typename StringType>
StringType substrBetween(const StringType& str, const StringType& delimiter1, const StringType& delimiter2);

template <typename StringType>
bool isPrefix(const StringType& prefix, const StringType& text);

template <typename StringType>
bool isPostfix(const StringType& postfix, const StringType& text);

std::string toUpperCase(const std::string& in);
std::wstring toUpperCase(const std::wstring& in);
std::string toLowerCase(const std::string& in);
std::wstring toLowerCase(const std::wstring& in);

template <typename StringType>
bool equalsCaseInsensitive(const std::string& a, const std::string& b);

std::string replace(std::string str, const std::string& from, const std::string& to);
std::wstring replace(std::wstring str, const std::wstring& from, const std::wstring& to);

std::string replaceBetween(const std::string& str, char startDelimiter, char endDelimiter, const std::string& to);
std::wstring replaceBetween(const std::wstring& str, wchar_t startDelimiter, wchar_t endDelimiter,
                            const std::wstring& to);

std::string insertLineBreaksAtBlankSpaces(const std::string& s, size_t maxLineLength);
std::wstring breakSignature(std::wstring signature, size_t maxLineLength, size_t tabWidth);
std::wstring breakSignature(std::wstring returnPart, std::wstring namePart, std::wstring paramPart,
                            size_t maxLineLength, size_t tabWidth);

std::string trim(const std::string& str);
std::wstring trim(const std::wstring& str);

enum ElideMode { ELIDE_LEFT, ELIDE_MIDDLE, ELIDE_RIGHT };

std::string elide(const std::string& str, ElideMode mode, size_t size);
std::wstring elide(const std::wstring& str, ElideMode mode, size_t size);

std::wstring convertWhiteSpacesToSingleSpaces(const std::wstring& str);

bool caseInsensitiveLess(const std::wstring& s1, const std::wstring& s2);

// Helper to determine whether there's a const_iterator for T.
template<typename T>
struct has_const_iterator {
private:
    template<typename C> static char test(typename C::const_iterator*);
    template<typename C> static int  test(...);
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

template<class ContainerType, class StringType>
ContainerType split(const StringType& str, const StringType& delimiter) {
  size_t pos = 0;
  size_t oldPos = 0;
  ContainerType container;

  do {
    pos = str.find(delimiter, oldPos);
    container.push_back(str.substr(oldPos, pos - oldPos));
    oldPos = pos + delimiter.size();
  } while (pos != StringType::npos);

  return container;
}

template <typename ContainerType, class StringType>
StringType join(const ContainerType& list, const StringType& delimiter) {
  std::basic_stringstream<typename StringType::value_type> stringstream;
  bool first = true;
  for (const std::string& str : list) {
    if (!first) {
      stringstream << delimiter;
    }
    first = false;

    stringstream << str;
  }
  return stringstream.str();
}

template <typename ContainerType>
std::wstring join(const ContainerType& list, const std::wstring& delimiter) {
  std::wstringstream ss;
  bool first = true;
  for (const std::wstring& str : list) {
    if (!first) {
      ss << delimiter;
    }
    first = false;

    ss << str;
  }
  return ss.str();
}

template <typename StringType>
StringType substrBetween(const StringType& str, const StringType& delimiter1, const StringType& delimiter2) {
  size_t found_delimiter1 = str.find(delimiter1);
  found_delimiter1 += delimiter1.length();
  size_t found_delimiter2 = str.find(delimiter2, found_delimiter1);
  if (found_delimiter1 != str.npos && found_delimiter2 != str.npos) {
    return str.substr(found_delimiter1, found_delimiter2 - found_delimiter1);
  }
  return StringType();
}

template <typename StringType>
bool isPrefix(const StringType& prefix, const StringType& text) {
  if (prefix.size() <= text.size()) {
    std::pair<typename StringType::const_iterator, typename StringType::const_iterator> res =
        std::mismatch(prefix.begin(), prefix.end(), text.begin());

    return res.first == prefix.end();
  }
  return false;
}

template <typename StringType>
bool isPostfix(const StringType& postfix, const StringType& text) {
  return text.size() >= postfix.size() && text.rfind(postfix) == (text.size() - postfix.size());
}

template <typename StringType>
bool equalsCaseInsensitive(const StringType& a, const StringType& b) {
  if (a.size() == b.size()) {
    return toLowerCase(a) == toLowerCase(b);
  }
  return false;
}

}  // namespace utility
