#ifndef SOURCE_GROUP_JAVA_H
#define SOURCE_GROUP_JAVA_H

#include <memory>
#include <set>
#include <vector>

#include "SourceGroup.h"

class SourceGroupJava: public SourceGroup
{
public:
	std::set<utility::file::FilePath> filterToContainedFilePaths(const std::set<utility::file::FilePath>& filePaths) const override;
	std::set<utility::file::FilePath> getAllSourceFilePaths() const override;
	std::vector<std::shared_ptr<IndexerCommand>> getIndexerCommands(const RefreshInfo& info) const override;

private:
	virtual std::vector<utility::file::FilePath> getAllSourcePaths() const = 0;
	virtual std::vector<utility::file::FilePath> doGetClassPath() const = 0;

	std::vector<utility::file::FilePath> getClassPath() const;
};

#endif	  // SOURCE_GROUP_JAVA_H
