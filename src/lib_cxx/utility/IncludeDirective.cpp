#include "IncludeDirective.h"

IncludeDirective::IncludeDirective(
	const utility::file::FilePath& includedFilePath,
	const utility::file::FilePath& includingFilePath,
	unsigned int lineNumber,
	bool usesBrackets)
	: m_includedFilePath(includedFilePath)
	, m_includingFilePath(includingFilePath)
	, m_lineNumber(lineNumber)
	, m_usesBrackets(usesBrackets)
{
}

utility::file::FilePath IncludeDirective::getIncludedFile() const
{
	return m_includedFilePath;
}

utility::file::FilePath IncludeDirective::getIncludingFile() const
{
	return m_includingFilePath;
}

std::wstring IncludeDirective::getDirective() const
{
	return std::wstring(L"#include ") + (m_usesBrackets ? L"<" : L"\"") +
		m_includedFilePath.wstr() + (m_usesBrackets ? L">" : L"\"");
}

unsigned int IncludeDirective::getLineNumber() const
{
	return m_lineNumber;
}
