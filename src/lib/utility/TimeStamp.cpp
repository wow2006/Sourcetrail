// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TimeStamp.hpp"

TimeStamp TimeStamp::now() { return TimeStamp(boost::posix_time::microsec_clock::local_time()); }

double TimeStamp::durationSeconds(const TimeStamp& start) { return double(TimeStamp::now().deltaMS(start)) / 1000.0; }

std::string TimeStamp::secondsToString(double seconds) {
  std::stringstream stream;

  int hours = int(seconds / 3600);
  seconds -= hours * 3600;

  int minutes = int(seconds / 60);
  seconds -= minutes * 60;

  int intSeconds = int(seconds);
  seconds -= intSeconds;

  const int milliSeconds = static_cast<int>(seconds * 1000);

  if (hours > 9) {
    stream << hours;
  } else {
    stream << std::setw(2) << std::setfill('0') << hours;
  }
  stream << ":" << std::setw(2) << std::setfill('0') << minutes;
  stream << ":" << std::setw(2) << std::setfill('0') << intSeconds;

  if (hours != 0 && minutes != 0) {
    stream << ":" << std::setw(3) << std::setfill('0') << milliSeconds;
  }

  return stream.str();
}

TimeStamp::TimeStamp() : m_time(boost::posix_time::not_a_date_time) {}

TimeStamp::TimeStamp(boost::posix_time::ptime time) : m_time(time) {}

TimeStamp::TimeStamp(const std::string& timeInString) : m_time(boost::posix_time::not_a_date_time) {
  if(!timeInString.empty()) {
    m_time = boost::posix_time::time_from_string(timeInString);
  }
}

bool TimeStamp::isValid() const { return m_time != boost::posix_time::not_a_date_time; }

std::string TimeStamp::toString() const {
  std::stringstream stream;
  auto* facet = new boost::posix_time::time_facet();
  facet->format("%Y-%m-%d %H:%M:%S");
  stream.imbue(std::locale(std::locale::classic(), facet));
  stream << m_time;
  return stream.str();
}

std::string TimeStamp::getDDMMYYYYString() const {
  std::stringstream stream;
  auto* facet = new boost::posix_time::time_facet();
  facet->format("%d-%m-%Y");
  stream.imbue(std::locale(std::locale::classic(), facet));
  stream << m_time;
  return stream.str();
}

std::string TimeStamp::dayOfWeek() const {
  switch (m_time.date().day_of_week()) {
    case 0:
      return "Sunday";
    case 1:
      return "Monday";
    case 2:
      return "Tuesday";
    case 3:
      return "Wednesday";
    case 4:
      return "Thursday";
    case 5:
      return "Friday";
    case 6:
      return "Saturday";
  }
  return "none";
}

std::string TimeStamp::dayOfWeekShort() const { return dayOfWeek().substr(0, 3); }

size_t TimeStamp::deltaMS(const TimeStamp& other) const {
  return static_cast<size_t>(abs((m_time - other.m_time).total_milliseconds()));
}

size_t TimeStamp::deltaS(const TimeStamp& other) const {
  return static_cast<size_t>(abs((m_time - other.m_time).total_seconds()));
}

bool TimeStamp::isSameDay(const TimeStamp& other) const {
  if (m_time.date().day() == other.m_time.date().day() && m_time.date().month() == other.m_time.date().month() &&
      m_time.date().year() == other.m_time.date().year()) {
    return true;
  }

  return false;
}

size_t TimeStamp::deltaDays(const TimeStamp& other) const {
  boost::gregorian::date_duration deltaDate = m_time.date() - other.m_time.date();
  return abs(deltaDate.days());
}

size_t TimeStamp::deltaHours(const TimeStamp& other) const {
  boost::posix_time::time_duration delta = m_time - other.m_time;
  return static_cast<size_t>(abs(delta.total_seconds() / 3600));
}
