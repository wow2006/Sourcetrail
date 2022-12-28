#include "TimeStamp.h"

TimeStamp TimeStamp::now() {
  return TimeStamp(boost::posix_time::microsec_clock::local_time());
}

double TimeStamp::durationSeconds(const TimeStamp& start) {
  constexpr auto MilisecondsToSeconds = 1000.0;
  return static_cast<double>(TimeStamp::now().deltaMS(start)) / MilisecondsToSeconds;
}

std::string TimeStamp::secondsToString(double secs) {
  std::stringstream stringstream;

  int hours = static_cast<int>(secs / 3600);
  secs -= hours * 3600;

  int minutes = static_cast<int>(secs / 60);
  secs -= minutes * 60;

  int seconds = static_cast<int>(secs);
  secs -= seconds;

  const int milliSeconds = static_cast<int>(secs * 1000);

  if(hours > 9) {
    stringstream << hours;
  } else {
    stringstream << std::setw(2) << std::setfill('0') << hours;
  }
  stringstream << ":" << std::setw(2) << std::setfill('0') << minutes;
  stringstream << ":" << std::setw(2) << std::setfill('0') << seconds;

  if(!hours && !minutes) {
    stringstream << ":" << std::setw(3) << std::setfill('0') << milliSeconds;
  }

  return stringstream.str();
}

TimeStamp::TimeStamp(): m_time(boost::posix_time::not_a_date_time) {}

TimeStamp::TimeStamp(boost::posix_time::ptime time): m_time(time) {}

TimeStamp::TimeStamp(const std::string& timeString): m_time(boost::posix_time::not_a_date_time) {
  if(!timeString.empty()) {
    m_time = boost::posix_time::time_from_string(timeString);
  }
}

bool TimeStamp::isValid() const {
  return m_time != boost::posix_time::not_a_date_time;
}

std::string TimeStamp::toString() const {
  std::stringstream stream;
  auto* facet = new boost::posix_time::time_facet(); // NOLINT(cppcoreguidelines-owning-memory)
  facet->format("%Y-%m-%d %H:%M:%S");
  stream.imbue(std::locale(std::locale::classic(), facet));
  stream << m_time;
  return stream.str();
}

std::string TimeStamp::getDDMMYYYYString() const {
  std::stringstream stream;
  auto* facet = new boost::posix_time::time_facet(); // NOLINT(cppcoreguidelines-owning-memory)
  facet->format("%d-%m-%Y");
  stream.imbue(std::locale(std::locale::classic(), facet));
  stream << m_time;
  return stream.str();
}

std::string TimeStamp::dayOfWeek() const {
  switch(m_time.date().day_of_week()) {
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

std::string TimeStamp::dayOfWeekShort() const {
  return dayOfWeek().substr(0, 3);
}

size_t TimeStamp::deltaMS(const TimeStamp& other) const {
  return static_cast<size_t>(std::abs((m_time - other.m_time).total_milliseconds()));
}

size_t TimeStamp::deltaS(const TimeStamp& other) const {
  return static_cast<size_t>(std::abs((m_time - other.m_time).total_seconds()));
}

size_t TimeStamp::deltaHours(const TimeStamp& other) const {
  const auto delta = m_time - other.m_time;
  return static_cast<size_t>(std::abs(delta.total_seconds() / 3600));
}

bool TimeStamp::isSameDay(const TimeStamp& other) const {
  return m_time.date().day()   == other.m_time.date().day() &&
         m_time.date().month() == other.m_time.date().month() &&
         m_time.date().year()  == other.m_time.date().year();
}

size_t TimeStamp::deltaDays(const TimeStamp& other) const {
  boost::gregorian::date_duration deltaDate = m_time.date() - other.m_time.date();
  return static_cast<size_t>(std::abs(deltaDate.days()));
}
