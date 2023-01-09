#ifndef INCLUDE_DIRECTIVE_H
#define INCLUDE_DIRECTIVE_H

#include "FilePath.h"

class IncludeDirective
{
public:
	IncludeDirective(
		const utility::file::FilePath& includedFilePath,
		const utility::file::FilePath& includingFilePath,
		unsigned int lineNumber,
		bool usesBrackets);

	utility::file::FilePath getIncludedFile() const;
	utility::file::FilePath getIncludingFile() const;
	std::wstring getDirective() const;
	unsigned int getLineNumber() const;

private:
	const utility::file::FilePath m_includedFilePath;
	const utility::file::FilePath m_includingFilePath;
	const unsigned int m_lineNumber;
	bool m_usesBrackets;
};

#endif	  // INCLUDE_DIRECTIVE_H
