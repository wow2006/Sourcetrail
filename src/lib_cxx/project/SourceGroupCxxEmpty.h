#pragma once

#include <memory>
#include <set>

#include "SourceGroup.h"

class SourceGroupSettingsCxx;

class SourceGroupCxxEmpty : public SourceGroup {
 public:
  explicit SourceGroupCxxEmpty(std::shared_ptr<SourceGroupSettings> settings);

  std::set<FilePath> filterToContainedFilePaths(const std::set<FilePath>& filePaths) const override;
  std::set<FilePath> getAllSourceFilePaths() const override;
  std::shared_ptr<IndexerCommandProvider> getIndexerCommandProvider(const RefreshInfo& info) const override;
  std::vector<std::shared_ptr<IndexerCommand>> getIndexerCommands(const RefreshInfo& info) const override;
  std::shared_ptr<Task> getPreIndexTask(std::shared_ptr<StorageProvider> storageProvider,
                                        std::shared_ptr<DialogView> dialogView) const override;

 private:
  std::shared_ptr<SourceGroupSettings> getSourceGroupSettings() override;
  std::shared_ptr<const SourceGroupSettings> getSourceGroupSettings() const override;
  std::vector<std::wstring> getBaseCompilerFlags() const;

  std::shared_ptr<SourceGroupSettings> m_settings;
};
