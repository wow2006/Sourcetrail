#ifndef MESSAGE_MOVE_IDE_CURSOR_H
#define MESSAGE_MOVE_IDE_CURSOR_H

#include "FilePath.h"
#include "Message.h"

class MessageMoveIDECursor: public Message<MessageMoveIDECursor>
{
public:
	MessageMoveIDECursor(const FilePath& filePath_, const unsigned int row_, const unsigned int column_)
		: filePath(filePath_), row(row_), column(column_)
	{
	}

	static const std::string getStaticType()
	{
		return "MessageMoveIDECursor";
	}

	virtual void print(std::wostream& os) const
	{
		os << filePath.wstr() << L":" << row << L":" << column;
	}

	const FilePath filePath;
	const unsigned int row;
	const unsigned int column;
};

#endif	  // MESSAGE_MOVE_IDE_CURSOR_H