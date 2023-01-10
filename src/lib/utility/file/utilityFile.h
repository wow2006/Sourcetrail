#pragma once
// Internal
#include "FilePath.h"

namespace utility::file {

/**
 * @brief Sort the files by file size
 *
 * @param filePaths list of files to sort
 * @param partitionCount partitioncount
 *
 * @return sorted list
 */
std::vector<FilePath> partitionFilePathsBySize(const std::vector<FilePath>& filePaths,
                                               uint32_t partitionCount = 0);

std::vector<FilePath> getTopLevelPaths(const std::vector<FilePath>& paths);

std::vector<FilePath> getTopLevelPaths(const std::set<FilePath>& paths);

FilePath getExpandedPath(const FilePath& path);

std::vector<FilePath> getExpandedPaths(const std::vector<FilePath>& paths);

FilePath getExpandedAndAbsolutePath(const FilePath& path, const FilePath& baseDirectory);

FilePath getAsRelativeIfShorter(const FilePath& absolutePath, const FilePath& baseDirectory);

std::vector<FilePath> getAsRelativeIfShorter(const std::vector<FilePath>& absolutePaths,
                                             const FilePath& baseDirectory);
}    // namespace utility::file
