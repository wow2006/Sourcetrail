#pragma once

#include "Message.h"

class MessageRefresh: public Message<MessageRefresh>
{
public:
	static const std::string getStaticType()
	{
		return "MessageRefresh";
	}

	MessageRefresh(): all(false) {}

	MessageRefresh& refreshAll()
	{
		all = true;
		return *this;
	}

	void print(std::wostream& os) const override
	{
		if (all)
		{
			os << "all";
		}
	}

	bool all;
};
