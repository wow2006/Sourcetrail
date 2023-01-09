#pragma once

namespace utility::file {
class FilePath;
struct FileInfo;
} // namespace class utility::file
class PersistentStorage;
struct RefreshInfo;
class SourceGroup;

class RefreshInfoGenerator {
public:
  static RefreshInfo getRefreshInfoForUpdatedFiles(
      const std::vector<std::shared_ptr<SourceGroup>>& sourceGroups,
      std::shared_ptr<const PersistentStorage> storage);

  static RefreshInfo getRefreshInfoForIncompleteFiles(
      const std::vector<std::shared_ptr<SourceGroup>>& sourceGroups,
      std::shared_ptr<const PersistentStorage> storage);

  static RefreshInfo getRefreshInfoForAllFiles(
      const std::vector<std::shared_ptr<SourceGroup>>& sourceGroups);

private:
  static std::set<utility::file::FilePath> getAllSourceFilePaths(
      const std::vector<std::shared_ptr<SourceGroup>>& sourceGroups);

  static bool didFileChange(const utility::file::FileInfo& info, std::shared_ptr<const PersistentStorage> storage);
};