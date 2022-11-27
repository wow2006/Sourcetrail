#ifndef ERROR_INFO_H
#define ERROR_INFO_H

#include <limits>

#include "StorageError.h"

struct ErrorInfo
{
	ErrorInfo()
		: id(0)
		, message(L"")
		, filePath(L"")
		, lineNumber(std::numeric_limits<size_t>::max())
		, columnNumber(std::numeric_limits<size_t>::max())
		, translationUnit(L"")
		, fatal(0)
		, indexed(0)
	{
	}

	ErrorInfo(
		Id id,
		std::wstring message,
		std::wstring filePath,
		size_t lineNumber,
		size_t columnNumber,
		std::wstring translationUnit,
		bool fatal,
		bool indexed)
		: id(id)
		, message(std::move(message))
		, filePath(std::move(filePath))
		, lineNumber(lineNumber)
		, columnNumber(columnNumber)
		, translationUnit(std::move(translationUnit))
		, fatal(fatal)
		, indexed(indexed)
	{
	}

	Id id;

	std::wstring message;

	std::wstring filePath;
	size_t lineNumber;
	size_t columnNumber;

	std::wstring translationUnit;
	bool fatal;
	bool indexed;
};

#endif	  // ERROR_INFO_H
