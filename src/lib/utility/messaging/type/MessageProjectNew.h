#ifndef MESSAGE_PROJECT_NEW_H
#define MESSAGE_PROJECT_NEW_H

#include "FilePath.h"
#include "Message.h"

class MessageProjectNew: public Message<MessageProjectNew>
{
public:
	MessageProjectNew(const FilePath& cdbPath_): cdbPath(cdbPath_) {}

	static const std::string getStaticType()
	{
		return "MessageProjectNew";
	}

	const FilePath cdbPath;
};

#endif	  // MESSAGE_PROJECT_NEW_H
