#ifndef MESSAGE_ERROR_COUNT_UPDATE_H
#define MESSAGE_ERROR_COUNT_UPDATE_H

#include "Message.h"

#include "ErrorCountInfo.h"

class MessageErrorCountUpdate: public Message<MessageErrorCountUpdate>
{
public:
	static const std::string getStaticType()
	{
		return "MessageErrorCountUpdate";
	}

	MessageErrorCountUpdate(const ErrorCountInfo& errorCount_, const std::vector<ErrorInfo>& newErrors_)
		: errorCount(errorCount_), newErrors(newErrors_)
	{
		setSendAsTask(false);
	}

	virtual void print(std::wostream& os) const
	{
		os << errorCount.total << '/' << errorCount.fatal << L" - " << newErrors.size()
		   << L" new errors";
	}

	const ErrorCountInfo errorCount;
	std::vector<ErrorInfo> newErrors;
};

#endif	  // MESSAGE_ERROR_COUNT_UPDATE_H
