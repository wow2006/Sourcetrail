#include "IndexerCommandJava.h"

#include <QJsonArray>
#include <QJsonObject>

#include "utilityString.h"

IndexerCommandType IndexerCommandJava::getStaticIndexerCommandType()
{
	return INDEXER_COMMAND_JAVA;
}

IndexerCommandJava::IndexerCommandJava(
	const utility::file::FilePath& sourceFilePath,
	const std::wstring& languageStandard,
	const std::vector<utility::file::FilePath>& classPath)
	: IndexerCommand(sourceFilePath), m_languageStandard(languageStandard), m_classPath(classPath)
{
}

IndexerCommandType IndexerCommandJava::getIndexerCommandType() const
{
	return getStaticIndexerCommandType();
}

size_t IndexerCommandJava::getByteSize(size_t stringSize) const
{
	size_t size = IndexerCommand::getByteSize(stringSize);

	for (const utility::file::FilePath& i: m_classPath)
	{
		size += stringSize + utility::encodeToUtf8(i.wstr()).size();
	}

	return size;
}

std::wstring IndexerCommandJava::getLanguageStandard() const
{
	return m_languageStandard;
}

void IndexerCommandJava::setClassPath(std::vector<utility::file::FilePath> classPath)
{
	m_classPath = classPath;
}

std::vector<utility::file::FilePath> IndexerCommandJava::getClassPath() const
{
	return m_classPath;
}

QJsonObject IndexerCommandJava::doSerialize() const
{
	QJsonObject jsonObject = IndexerCommand::doSerialize();

	{
		QJsonArray classPathArray;
		for (const utility::file::FilePath& classPath: m_classPath)
		{
			classPathArray.append(QString::fromStdWString(classPath.wstr()));
		}
		jsonObject["class_path"] = classPathArray;
	}
	{
		jsonObject["language_standard"] = QString::fromStdWString(m_languageStandard);
	}

	return jsonObject;
}
