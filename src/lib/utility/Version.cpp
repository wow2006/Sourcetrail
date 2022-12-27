#include "Version.h"
// STL
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

inline constexpr auto MinMinorNumber = 0;
inline constexpr auto MaxMinorNumber = 5;
inline constexpr auto MinYear        = 2016;

Version Version::s_version;    // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

Version Version::fromString(const std::string& versionString) {
  constexpr auto Regex = R"((\d{4})\.(\d)\.(\d+)?\-(\w{8})?)";
  std::smatch matches;
  if(std::regex_search(versionString, matches, std::regex(Regex))) {
    Version version;
    try {
      version.m_year = std::stoi(matches[1].str());
      version.m_minorNumber = std::stoi(matches[2].str());
      if(matches.size() > 3) {
        version.m_commitNumber = std::stoi(matches[3].str());
      }
      if(matches.size() > 4) {
        version.m_commitHash = matches[4].str();
      }
      return version;
    } catch(std::invalid_argument const& ex) {
      // ...
    }
  }

  return Version{};
}

void Version::setApplicationVersion(const Version& version) {
  s_version = version;
}

const Version& Version::getApplicationVersion() {
  return s_version;
}

Version::Version(int year, int minor, int commit, std::string hash)
    : m_year(year), m_minorNumber(minor), m_commitNumber(commit), m_commitHash(std::move(hash)) {}

bool Version::isEmpty() const {
  return m_year == 0 && m_minorNumber == 0 && m_commitNumber == 0;
}

bool Version::isValid() const {
  return (MinMinorNumber < m_minorNumber && m_minorNumber < MaxMinorNumber && m_year > MinYear);
}

Version Version::toShortVersion() const {
  return Version{m_year, m_minorNumber};
}

std::string Version::toShortString() const {
  std::stringstream stringstream;
  stringstream << m_year << '.' << m_minorNumber;
  return stringstream.str();
}

std::string Version::toString() const {
  std::stringstream stringstream;
  stringstream << m_year << '.' << m_minorNumber << '-' << m_commitNumber << '-' << m_commitHash;
  return stringstream.str();
}

std::string Version::toDisplayString() const {
  return std::to_string(m_year) + '.' + std::to_string(m_minorNumber) + '.' +
      std::to_string(m_commitNumber);
}

std::wstring Version::toDisplayWString() const {
  return std::to_wstring(m_year) + L'.' + std::to_wstring(m_minorNumber) + L'.' +
      std::to_wstring(m_commitNumber);
}

bool Version::operator<(const Version& other) const {
  if(m_year != other.m_year) {
    return m_year < other.m_year;
  }

  if(m_minorNumber != other.m_minorNumber) {
    return m_minorNumber < other.m_minorNumber;
  }

  return m_commitNumber < other.m_commitNumber;
}

bool Version::operator>(const Version& other) const {
  if(m_year != other.m_year) {
    return m_year > other.m_year;
  }

  if(m_minorNumber != other.m_minorNumber) {
    return m_minorNumber > other.m_minorNumber;
  }

  return m_commitNumber > other.m_commitNumber;
}

bool Version::operator==(const Version& other) const {
  return m_year == other.m_year && m_minorNumber == other.m_minorNumber &&
      m_commitNumber == other.m_commitNumber;
}

Version& Version::operator+=(const int& number) {
  int minor = this->m_minorNumber - 1 + number;
  this->m_year += minor / 4;
  this->m_minorNumber = (minor % 4) + 1;
  return *this;
}
