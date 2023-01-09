#include "utilityFile.h"

#include "FileSystem.h"
#include "logging.h"
#include "utility.h"

namespace utility::file {

std::vector<FilePath> partitionFilePathsBySize(const std::vector<FilePath>& filePaths,
                                               int partitionCount) {
  using PairType = std::pair<uint64_t, FilePath>;
  std::vector<PairType> sourceFileSizesToCommands;
  for(const FilePath& path: filePaths) {
    if(path.exists()) {
      sourceFileSizesToCommands.emplace_back(FileSystem::getFileByteSize(path), path);
    } else {
      sourceFileSizesToCommands.emplace_back(1, path);
    }
  }

  std::sort(sourceFileSizesToCommands.begin(),
            sourceFileSizesToCommands.end(),
            [](const PairType& aType, const PairType& bType) { return aType.first > bType.first; });

  if(0 < partitionCount && partitionCount < static_cast<int>(sourceFileSizesToCommands.size())) {
    for(int i = 0; i < partitionCount; i++) {
      std::sort(
          sourceFileSizesToCommands.begin() + sourceFileSizesToCommands.size() * i / partitionCount,
          sourceFileSizesToCommands.begin() +
              sourceFileSizesToCommands.size() * (i + 1) / partitionCount,
          [](const PairType& aType, const PairType& bType) {
            return aType.second.wstr() < bType.second.wstr();
          });
    }
  }

  std::vector<FilePath> sortedFilePaths;
  sortedFilePaths.reserve(sourceFileSizesToCommands.size());
  for(const PairType& pair: sourceFileSizesToCommands) {
    sortedFilePaths.push_back(pair.second);
  }
  return sortedFilePaths;
}

std::vector<FilePath> getTopLevelPaths(const std::vector<FilePath>& paths) {
  return getTopLevelPaths(utility::toSet(paths));
}

std::vector<FilePath> getTopLevelPaths(const std::set<FilePath>& paths) {
  // this works because the set contains the paths already in alphabetical order
  std::vector<FilePath> topLevelPaths;

  FilePath lastPath;
  for(const FilePath& path: paths) {
    if(lastPath.empty() ||
       !lastPath.contains(path))    // don't add subdirectories of already added paths
    {
      lastPath = path;
      topLevelPaths.push_back(path);
    }
  }

  return topLevelPaths;
}

FilePath getExpandedPath(const FilePath& path) {
  std::vector<FilePath> paths = path.expandEnvironmentVariables();
  if(!paths.empty()) {
    if(paths.size() > 1) {
      LOG_WARNING(L"Environment variable in path \"" + path.wstr() + L"\" has been expanded to " +
                  std::to_wstring(paths.size()) + L"paths, but only \"" + paths.front().wstr() +
                  L"\" will be used.");
    }
    return paths.front();
  }
  return {};
}

std::vector<FilePath> getExpandedPaths(const std::vector<FilePath>& paths) {
  std::vector<FilePath> expandedPaths;
  for(const FilePath& path: paths) {
    utility::append(expandedPaths, path.expandEnvironmentVariables());
  }
  return expandedPaths;
}

FilePath getExpandedAndAbsolutePath(const FilePath& path, const FilePath& baseDirectory) {
  FilePath expandedPath = getExpandedPath(path);

  if(expandedPath.empty() || expandedPath.isAbsolute()) {
    return expandedPath;
  }

  return baseDirectory.getConcatenated(expandedPath).makeCanonical();
}

FilePath getAsRelativeIfShorter(const FilePath& absolutePath, const FilePath& baseDirectory) {
  if(!baseDirectory.empty()) {
    FilePath relativePath = absolutePath.getRelativeTo(baseDirectory);
    if(relativePath.wstr().size() < absolutePath.wstr().size()) {
      return relativePath;
    }
  }
  return absolutePath;
}

std::vector<FilePath> getAsRelativeIfShorter(const std::vector<FilePath>& absolutePaths,
                                             const FilePath& baseDirectory) {
  return utility::convert<FilePath, FilePath>(absolutePaths, [&](const FilePath& path) {
    return getAsRelativeIfShorter(path, baseDirectory);
  });
}

}    // namespace utility::file
