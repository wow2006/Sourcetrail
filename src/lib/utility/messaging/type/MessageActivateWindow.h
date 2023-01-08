#pragma once

#include "Message.h"

class MessageActivateWindow: public Message<MessageActivateWindow>
{
public:
	MessageActivateWindow() {}

	static const std::string getStaticType()
	{
		return "MessageActivateWindow";
	}
};
