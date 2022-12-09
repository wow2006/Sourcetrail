#ifndef ERROR_FILTER_H
#define ERROR_FILTER_H

#include "ErrorInfo.h"

struct ErrorFilter {
  ErrorFilter() : error(true), fatal(true), unindexedError(true), unindexedFatal(true), limit(1000) {}

  bool filter(const ErrorInfo& info) const {
    if (!error && !info.fatal && info.indexed) return false;
    if (!fatal && info.fatal && info.indexed) return false;
    if (!unindexedError && !info.fatal && !info.indexed) return false;
    if (!unindexedFatal && info.fatal && !info.indexed) return false;
    return true;
  }

  std::vector<ErrorInfo> filterErrors(const std::vector<ErrorInfo>& errors) const {
    std::vector<ErrorInfo> filteredErrors;

    for (const ErrorInfo& error : errors) {
      if (filter(error)) {
        filteredErrors.push_back(error);

        if (limit > 0 && filteredErrors.size() >= limit) {
          break;
        }
      }
    }

    return filteredErrors;
  }

  bool operator==(const ErrorFilter& other) const {
    return error == other.error && fatal == other.fatal && unindexedError == other.unindexedError &&
           unindexedFatal == other.unindexedFatal && limit == other.limit;
  }

  bool error;
  bool fatal;

  bool unindexedError;
  bool unindexedFatal;

  size_t limit;
};

#endif  // ERROR_FILTER_H
