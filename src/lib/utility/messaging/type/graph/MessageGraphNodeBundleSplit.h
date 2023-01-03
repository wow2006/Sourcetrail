#ifndef MESSAGE_GRAPH_NODE_BUNDLE_SPLIT_H
#define MESSAGE_GRAPH_NODE_BUNDLE_SPLIT_H

#include "Message.h"
#include "TabId.h"
#include "types.h"

class MessageGraphNodeBundleSplit: public Message<MessageGraphNodeBundleSplit>
{
public:
	MessageGraphNodeBundleSplit(Id bundleId_, bool removeOtherNodes_ = false, bool layoutToList_ = false)
		: bundleId(bundleId_), removeOtherNodes(removeOtherNodes_), layoutToList(layoutToList_)
	{
		setSchedulerId(TabId::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageGraphNodeBundleSplit";
	}

	virtual void print(std::wostream& os) const
	{
		os << bundleId;
	}

	Id bundleId;
	bool removeOtherNodes;
	bool layoutToList;
};

#endif	  // MESSAGE_GRAPH_NODE_BUNDLE_SPLIT_H
