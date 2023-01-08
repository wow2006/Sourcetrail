#pragma once

#include "Message.h"
#include "SearchMatch.h"

class MessageTabState: public Message<MessageTabState>
{
public:
	MessageTabState(Id tabId_, const std::vector<SearchMatch>& searchMatches_)
		: tabId(tabId_), searchMatches(searchMatches_)
	{
	}

	static const std::string getStaticType()
	{
		return "MessageTabState";
	}

	const Id tabId;
	const std::vector<SearchMatch> searchMatches;
};
