#ifndef UTILITY_FILE_H
#define UTILITY_FILE_H

#include <set>
#include <vector>

class FilePath;

namespace utility {
std::vector<FilePath> partitionFilePathsBySize(std::vector<FilePath> filePaths, int partitionCount = 0);

std::vector<FilePath> getTopLevelPaths(const std::vector<FilePath>& paths);
std::vector<FilePath> getTopLevelPaths(const std::set<FilePath>& paths);

FilePath getExpandedPath(const FilePath& path);
std::vector<FilePath> getExpandedPaths(const std::vector<FilePath>& paths);
FilePath getExpandedAndAbsolutePath(const FilePath& path, const FilePath& baseDirectory);

FilePath getAsRelativeIfShorter(const FilePath& absolutePath, const FilePath& baseDirectory);
std::vector<FilePath> getAsRelativeIfShorter(const std::vector<FilePath>& absolutePaths, const FilePath& baseDirectory);
}  // namespace utility

#endif  // UTILITY_FILE_H
