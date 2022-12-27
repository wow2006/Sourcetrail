#pragma once
// STL
#include <mutex>
#include <stack>
#include <string>
#include <thread>
// Internal
#include "FilePath.h"
#include "TimeStamp.h"
#include "types.h"
#include "utilityString.h"

// #define TRACING_ENABLED
// #define USE_ACCUMULATED_TRACING

struct TraceEvent final {
public:
  TraceEvent() = default;

  TraceEvent(std::string eventName, Id id, size_t depth)
      : eventName(std::move(eventName)), id(id), depth(depth) {}

  std::string eventName;
  Id id = 0;
  size_t depth = 0;

  std::string functionName;
  std::string locationName;

  double time = 0.0;
};

class Tracer final {
public:
  static Tracer* getInstance();

  Tracer(const Tracer&) = delete;
  void operator=(const Tracer&) = delete;

  std::shared_ptr<TraceEvent> startEvent(const std::string& eventName);
  void finishEvent(const std::shared_ptr<TraceEvent>& event);

  void printTraces();

private:
  static std::shared_ptr<Tracer> s_instance;
  static Id s_nextTraceId;

  Tracer() noexcept;

  std::map<std::thread::id, std::vector<std::shared_ptr<TraceEvent>>> m_events;
  std::map<std::thread::id, std::stack<TraceEvent*>> m_startedEvents;

  std::mutex m_mutex;
};


class AccumulatingTracer final {
public:
  static AccumulatingTracer* getInstance();

  AccumulatingTracer(const AccumulatingTracer&) = delete;
  AccumulatingTracer& operator=(const AccumulatingTracer&) = delete;

  std::shared_ptr<TraceEvent> startEvent(const std::string& eventName);
  void finishEvent(const std::shared_ptr<TraceEvent>& event);

  void printTraces();

private:
  struct AccumulatedTraceEvent final {
    TraceEvent event;
    size_t count = {};
    double time = {};
  };

  static std::shared_ptr<AccumulatingTracer> s_instance;
  static Id s_nextTraceId;

  AccumulatingTracer();

  std::map<std::string, AccumulatedTraceEvent> m_accumulatedEvents;
  std::map<std::thread::id, std::stack<TraceEvent*>> m_startedEvents;

  std::mutex m_mutex;
};


template <typename TracerType>
class ScopedTrace final {
public:
  ScopedTrace(const std::string& eventName,
              const std::string& fileName,
              int lineNumber,
              const std::string& functionName);
  ~ScopedTrace();

  ScopedTrace(const ScopedTrace&) = delete;
  ScopedTrace operator=(const ScopedTrace&) = delete;
  ScopedTrace(ScopedTrace&&) = delete;
  ScopedTrace operator=(ScopedTrace&&) = delete;

private:
  std::shared_ptr<TraceEvent> m_event;
  TimeStamp m_timeStamp;
};

template <typename TracerType>
ScopedTrace<TracerType>::ScopedTrace(const std::string& eventName,
                                     const std::string& fileName,
                                     int lineNumber,
                                     const std::string& functionName)
    : m_event(TracerType::getInstance()->startEvent(eventName)) {
  m_event->functionName = functionName;
  m_event->locationName = utility::encodeToUtf8(FilePath(fileName).fileName()) + ":" +
      std::to_string(lineNumber);

  m_timeStamp = TimeStamp::now();
}

template <typename TracerType>
ScopedTrace<TracerType>::~ScopedTrace() {
  m_event->time = TimeStamp::durationSeconds(m_timeStamp);
  TracerType::getInstance()->finishEvent(m_event);
}

#ifdef TRACING_ENABLED
#  ifdef USE_ACCUMULATED_TRACING
#    define TRACE(__name__)                                                                        \
      ScopedTrace<AccumulatingTracer> __trace__(                                                   \
          std::string(__name__), __FILE__, __LINE__, __FUNCTION__)
#    define PRINT_TRACES() AccumulatingTracer::getInstance()->printTraces()
#  else
#    define TRACE(__name__)                                                                        \
      ScopedTrace<Tracer> __trace__(std::string(__name__), __FILE__, __LINE__, __FUNCTION__)
#    define PRINT_TRACES() Tracer::getInstance()->printTraces()
#  endif
#else
#  define TRACE(__name__)
#  define PRINT_TRACES()
#endif
