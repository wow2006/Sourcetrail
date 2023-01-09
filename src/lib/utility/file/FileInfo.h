#pragma once
// Internal
#include "TimeStamp.h"
#include "FilePath.h"

namespace utility::file {

struct FileInfo {
  FileInfo();

  FileInfo(const utility::file::FilePath& path);

  FileInfo(const utility::file::FilePath& path, const TimeStamp& lastWriteTime);

  utility::file::FilePath path;

  TimeStamp lastWriteTime;
};

}    // namespace utility::file
