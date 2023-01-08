#include "FileInfo.h"

FileInfo::FileInfo(): path(FilePath(L"")) {}

FileInfo::FileInfo(const FilePath& path_): path(path_) {}

FileInfo::FileInfo(const FilePath& path_, const TimeStamp& lastWriteTime_)
    : path(path_), lastWriteTime(lastWriteTime_) {}
