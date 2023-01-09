#include "FileInfo.h"

namespace utility::file {

FileInfo::FileInfo(): path(utility::file::FilePath(L"")) {}

FileInfo::FileInfo(const utility::file::FilePath& path_): path(path_) {}

FileInfo::FileInfo(const utility::file::FilePath& path_, const TimeStamp& lastWriteTime_)
    : path(path_), lastWriteTime(lastWriteTime_) {}

}    // namespace utility::file
