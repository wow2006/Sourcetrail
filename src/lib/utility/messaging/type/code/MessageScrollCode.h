#ifndef MESSAGE_SCROLL_CODE_H
#define MESSAGE_SCROLL_CODE_H

#include "Message.h"
#include "TabId.h"

class MessageScrollCode: public Message<MessageScrollCode>
{
public:
	MessageScrollCode(int value_, bool inListMode_): value(value_), inListMode(inListMode_)
	{
		setIsLogged(false);
		setSchedulerId(TabId::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageScrollCode";
	}

	int value;
	bool inListMode;
};

#endif	  // MESSAGE_SCROLL_CODE_H
