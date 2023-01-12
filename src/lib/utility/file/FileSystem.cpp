#include "FileSystem.h"

#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/filesystem.hpp>

#include "utilityString.h"

namespace fs = std::filesystem;

namespace utility::file {

std::vector<FilePath> FileSystem::getFilePathsFromDirectory(
    const FilePath& path, const std::vector<std::wstring>& extensions) {
  std::set<std::wstring> ext(extensions.begin(), extensions.end());
  std::vector<FilePath> files;

  if(path.isDirectory()) {
    boost::filesystem::recursive_directory_iterator iterator(path.getPath());
    boost::filesystem::recursive_directory_iterator endIterator;
    while(iterator != endIterator) {
      if(boost::filesystem::is_symlink(*iterator)) {
        // check for self-referencing symlinks
        auto selfPath = boost::filesystem::read_symlink(*iterator);
        if(selfPath.filename() == selfPath.string() &&
           selfPath.filename() == iterator->path().filename()) {
          ++iterator;
          continue;
        }
      }

      if(boost::filesystem::is_regular_file(*iterator) &&
         (ext.empty() || ext.find(iterator->path().extension().wstring()) != ext.end())) {
        files.emplace_back(iterator->path().generic_wstring());
      }
      ++iterator;
    }
  }
  return files;
}

FileInfo FileSystem::getFileInfoForPath(const FilePath& filePath) {
  if(filePath.exists()) {
    return {filePath, getLastWriteTime(filePath)};
  }
  return {};
}

std::vector<FileInfo> FileSystem::getFileInfosFromPaths(const std::vector<FilePath>& paths,
                                                        const std::vector<std::wstring>& fileExtensions,
                                                        bool followSymLinks) {
  std::set<std::wstring> ext;
  for(const auto& extension : fileExtensions) {
    ext.insert(utility::toLowerCase(extension));
  }

  std::set<boost::filesystem::path> symlinkDirs;
  std::set<FilePath> filePaths;

  std::vector<FileInfo> files;

  for(const FilePath& path : paths) {
    if(path.isDirectory()) {
      boost::filesystem::recursive_directory_iterator iterator(
          path.getPath(), boost::filesystem::symlink_option::recurse);
      boost::filesystem::recursive_directory_iterator endit;
      boost::system::error_code errorCode;
      for(; iterator != endit; iterator.increment(errorCode)) {
        if(boost::filesystem::is_symlink(*iterator)) {
          if(!followSymLinks) {
            iterator.no_push();
            continue;
          }

          // check for self-referencing symlinks
          auto selfPath = boost::filesystem::read_symlink(*iterator);
          if(selfPath.filename() == selfPath.string() &&
             selfPath.filename() == iterator->path().filename()) {
            continue;
          }

          // check for duplicates when following directory symlinks
          if(boost::filesystem::is_directory(*iterator)) {
            auto absDir = boost::filesystem::canonical(selfPath, iterator->path().parent_path());

            if(symlinkDirs.find(absDir) != symlinkDirs.end()) {
              iterator.no_push();
              continue;
            }

            symlinkDirs.insert(absDir);
          }
        }

        if(boost::filesystem::is_regular_file(*iterator) &&
           (ext.empty() ||
            ext.find(utility::toLowerCase(iterator->path().extension().wstring())) != ext.end())) {
          const auto canonicalPath = FilePath(iterator->path().wstring()).getCanonical();
          if(filePaths.find(canonicalPath) != filePaths.end()) {
            continue;
          }
          filePaths.insert(canonicalPath);
          files.push_back(getFileInfoForPath(canonicalPath));
        }
      }
    } else if(path.exists() &&
              (ext.empty() || ext.find(utility::toLowerCase(path.extension())) != ext.end())) {
      const FilePath canonicalPath = path.getCanonical();
      if(filePaths.find(canonicalPath) != filePaths.end()) {
        continue;
      }
      filePaths.insert(canonicalPath);
      files.push_back(getFileInfoForPath(canonicalPath));
    }
  }

  return files;
}

std::set<FilePath> FileSystem::getSymLinkedDirectories(const FilePath& path) {
  return getSymLinkedDirectories(std::vector<FilePath> {path});
}

std::set<FilePath> FileSystem::getSymLinkedDirectories(const std::vector<FilePath>& paths) {
  std::set<boost::filesystem::path> symlinkDirs;

  for(const auto& path : paths) {
    if(path.isDirectory()) {
      boost::filesystem::recursive_directory_iterator iterator(
          path.getPath(), boost::filesystem::symlink_option::recurse);
      boost::filesystem::recursive_directory_iterator endit;
      boost::system::error_code errorCode;
      for(; iterator != endit; iterator.increment(errorCode)) {
        if(boost::filesystem::is_symlink(*iterator)) {
          // check for self-referencing symlinks
          auto selfPath = boost::filesystem::read_symlink(*iterator);
          if(selfPath.filename() == selfPath.string() &&
             selfPath.filename() == iterator->path().filename()) {
            continue;
          }

          // check for duplicates when following directory symlinks
          if(boost::filesystem::is_directory(*iterator)) {
            auto absDir = boost::filesystem::canonical(selfPath, iterator->path().parent_path());

            if(symlinkDirs.find(absDir) != symlinkDirs.end()) {
              iterator.no_push();
              continue;
            }

            symlinkDirs.insert(absDir);
          }
        }
      }
    }
  }

  std::set<FilePath> files;
  for(const auto& dir : symlinkDirs) {
    files.insert(FilePath(dir.wstring()));
  }
  return files;
}

uint64_t FileSystem::getFileByteSize(const FilePath& filePath) {
  return boost::filesystem::file_size(filePath.getPath());
}

TimeStamp FileSystem::getLastWriteTime(const FilePath& filePath) {
  boost::posix_time::ptime lastWriteTime;
  if(filePath.exists()) {
    std::time_t time = boost::filesystem::last_write_time(filePath.getPath());
    lastWriteTime = boost::posix_time::from_time_t(time);
    lastWriteTime = boost::date_time::c_local_adjustor<boost::posix_time::ptime>::utc_to_local(
        lastWriteTime);
  }
  return TimeStamp {lastWriteTime};
}

bool FileSystem::remove(const FilePath& path) {
  boost::system::error_code errorCode;
  const bool ret = boost::filesystem::remove(path.getPath(), errorCode);
  path.recheckExists();
  return ret;
}

bool FileSystem::rename(const FilePath& fromPath, const FilePath& toPath) {
  if(!fromPath.recheckExists() || toPath.recheckExists()) {
    return false;
  }

  boost::filesystem::rename(fromPath.getPath(), toPath.getPath());
  toPath.recheckExists();
  return true;
}

bool FileSystem::copyFile(const FilePath& fromPath, const FilePath& toPath) {
  if(!fromPath.recheckExists() || toPath.recheckExists()) {
    return false;
  }

  boost::filesystem::copy_file(fromPath.getPath(), toPath.getPath());
  toPath.recheckExists();
  return true;
}

bool FileSystem::createDirectory(const FilePath& directory) {
  std::error_code errorCode;
  return std::filesystem::create_directories(directory.str(), errorCode);
}

std::vector<FilePath> FileSystem::getDirectSubDirectories(const FilePath& directory) {
  std::vector<FilePath> subDirectories;

  if(directory.exists() && directory.isDirectory()) {
    for(boost::filesystem::directory_iterator end, dir(directory.str()); dir != end; dir++) {
      if(boost::filesystem::is_directory(dir->path())) {
        subDirectories.emplace_back(dir->path().wstring());
      }
    }
  }

  return subDirectories;
}

std::vector<FilePath> FileSystem::getRecursiveSubDirectories(const FilePath& directory) {
  std::vector<FilePath> subDirectories;

  if(directory.exists() && directory.isDirectory()) {
    for(boost::filesystem::recursive_directory_iterator end, dir(directory.str()); dir != end; ++dir) {
      if(boost::filesystem::is_directory(dir->path())) {
        subDirectories.emplace_back(dir->path().wstring());
      }
    }
  }

  return subDirectories;
}

}    // namespace utility::file
