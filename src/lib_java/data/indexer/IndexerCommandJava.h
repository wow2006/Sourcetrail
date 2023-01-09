#ifndef INDEXER_COMMAND_JAVA_H
#define INDEXER_COMMAND_JAVA_H

#include <vector>

#include "IndexerCommand.h"

namespace utility::file {
class FilePath;
} // namespace class utility::file
class FilePathFilter;

class IndexerCommandJava: public IndexerCommand
{
public:
	static IndexerCommandType getStaticIndexerCommandType();

	IndexerCommandJava(
		const utility::file::FilePath& sourceFilePath,
		const std::wstring& languageStandard,
		const std::vector<utility::file::FilePath>& classPath);

	IndexerCommandType getIndexerCommandType() const override;
	size_t getByteSize(size_t stringSize) const override;

	std::wstring getLanguageStandard() const;

	void setClassPath(std::vector<utility::file::FilePath> classPath);
	std::vector<utility::file::FilePath> getClassPath() const;

protected:
	QJsonObject doSerialize() const override;

private:
	const std::wstring m_languageStandard;
	std::vector<utility::file::FilePath> m_classPath;
};

#endif	  // INDEXER_COMMAND_JAVA_H
