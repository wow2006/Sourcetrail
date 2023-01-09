#ifndef SOURCE_GROUP_CXX_CDB_H
#define SOURCE_GROUP_CXX_CDB_H

#include <memory>
#include <set>
#include <vector>

#include "SourceGroup.h"

namespace utility::file {
class FilePath;
} // namespace class utility::file
namespace clang
{
namespace tooling
{
class JSONCompilationDatabase;
}
}	 // namespace clang

class SourceGroupSettingsCxxCdb;

class SourceGroupCxxCdb: public SourceGroup
{
public:
	SourceGroupCxxCdb(std::shared_ptr<SourceGroupSettingsCxxCdb> settings);

	bool prepareIndexing() override;
	std::set<utility::file::FilePath> filterToContainedFilePaths(const std::set<utility::file::FilePath>& filePaths) const override;
	std::set<utility::file::FilePath> getAllSourceFilePaths() const override;
	std::set<utility::file::FilePath> getAllSourceFilePaths(
		std::shared_ptr<clang::tooling::JSONCompilationDatabase> cdb) const;
	std::shared_ptr<IndexerCommandProvider> getIndexerCommandProvider(
		const RefreshInfo& info) const override;
	std::vector<std::shared_ptr<IndexerCommand>> getIndexerCommands(const RefreshInfo& info) const override;
	std::shared_ptr<Task> getPreIndexTask(
		std::shared_ptr<StorageProvider> storageProvider,
		std::shared_ptr<DialogView> dialogView) const override;

private:
	std::shared_ptr<SourceGroupSettings> getSourceGroupSettings() override;
	std::shared_ptr<const SourceGroupSettings> getSourceGroupSettings() const override;
	std::vector<std::wstring> getBaseCompilerFlags() const;

	std::shared_ptr<SourceGroupSettingsCxxCdb> m_settings;
};

#endif	  // SOURCE_GROUP_CXX_CDB_H
