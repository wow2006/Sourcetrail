#ifndef MESSAGE_ACTIVATE_FILE_H
#define MESSAGE_ACTIVATE_FILE_H

#include "FilePath.h"
#include "Message.h"
#include "TabId.h"

class MessageActivateFile: public Message<MessageActivateFile>
{
public:
	MessageActivateFile(const FilePath& filePath_, unsigned int line_ = 0)
		: filePath(filePath_), line(line_)
	{
		setSchedulerId(TabId::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageActivateFile";
	}

	virtual void print(std::wostream& os) const
	{
		os << filePath.wstr();
	}

	const FilePath filePath;
	unsigned int line;
};

#endif	  // MESSAGE_ACTIVATE_FILE_H
