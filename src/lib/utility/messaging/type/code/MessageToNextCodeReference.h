#ifndef MESSAGE_TO_NEXT_CODE_REFERENCE_H
#define MESSAGE_TO_NEXT_CODE_REFERENCE_H

#include "Message.h"
#include "TabId.h"

class MessageToNextCodeReference: public Message<MessageToNextCodeReference>
{
public:
	MessageToNextCodeReference(const FilePath& filePath_, size_t lineNumber_, size_t columnNumber_, bool next_)
		: filePath(filePath), lineNumber(lineNumber_), columnNumber(columnNumber_), next(next_)
	{
		setSchedulerId(TabId::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageToNextCodeReference";
	}

	virtual void print(std::wostream& os) const
	{
		os << filePath.wstr() << L' ' << lineNumber << L':' << columnNumber << L' ';

		if (next)
		{
			os << L"next";
		}
		else
		{
			os << L"previous";
		}
	}

	const FilePath filePath;
	const size_t lineNumber;
	const size_t columnNumber;
	const bool next;
};

#endif	  // MESSAGE_TO_NEXT_CODE_REFERENCE_H
