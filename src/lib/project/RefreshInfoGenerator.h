#pragma once

struct FileInfo;
class FilePath;
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
  static std::set<FilePath> getAllSourceFilePaths(
      const std::vector<std::shared_ptr<SourceGroup>>& sourceGroups);

  static bool didFileChange(const FileInfo& info, std::shared_ptr<const PersistentStorage> storage);
};