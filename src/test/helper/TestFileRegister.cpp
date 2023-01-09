#include "TestFileRegister.h"

#include "FilePathFilter.h"

TestFileRegister::TestFileRegister()
    : FileRegister(utility::file::FilePath(), std::set<utility::file::FilePath>(), {utility::file::FilePathFilter(L"")}) {}

TestFileRegister::~TestFileRegister() = default;

bool TestFileRegister::hasFilePath(const utility::file::FilePath& /*filePath*/) const {
  return true;
}
