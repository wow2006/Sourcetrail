#pragma once

#include "Bookmark.h"
#include "Message.h"

class MessageBookmarkActivate: public Message<MessageBookmarkActivate>
{
public:
	MessageBookmarkActivate(const std::shared_ptr<Bookmark>& bookmark_): bookmark(bookmark_) {}

	static const std::string getStaticType()
	{
		return "MessageBookmarkActivate";
	}

	const std::shared_ptr<Bookmark> bookmark;
};
