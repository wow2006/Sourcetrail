#ifndef MESSAGE_BOOKMARKS_BROWSE_H
#define MESSAGE_BOOKMARKS_BROWSE_H

#include "Bookmark.h"
#include "Message.h"

class MessageBookmarkBrowse: public Message<MessageBookmarkBrowse>
{
public:
	MessageBookmarkBrowse(
		Bookmark::BookmarkFilter filter_ = Bookmark::FILTER_UNKNOWN,
		Bookmark::BookmarkOrder order_ = Bookmark::ORDER_NONE)
		: filter(filter_), order(order_)
	{
	}

	static const std::string getStaticType()
	{
		return "MessageBookmarkBrowse";
	}

	const Bookmark::BookmarkFilter filter;
	const Bookmark::BookmarkOrder order;
};

#endif	  // MESSAGE_BOOKMARKS_BROWSE_H
