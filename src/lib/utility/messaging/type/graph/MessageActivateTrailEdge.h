#ifndef MESSAGE_ACTIVATE_TRAIL_EDGE_H
#define MESSAGE_ACTIVATE_TRAIL_EDGE_H

#include "Edge.h"
#include "NameHierarchy.h"

#include "Message.h"
#include "TabId.h"
#include "types.h"
#include "utilityString.h"

class MessageActivateTrailEdge: public Message<MessageActivateTrailEdge>
{
public:
	MessageActivateTrailEdge(
		const std::vector<Id>& edgeIds_,
		Edge::EdgeType type_,
		const NameHierarchy& sourceNameHierarchy_,
		const NameHierarchy& targetNameHierarchy_)
		: edgeIds(edgeIds_)
		, type(type_)
		, sourceNameHierarchy(sourceNameHierarchy_)
		, targetNameHierarchy(targetNameHierarchy_)
	{
		setSchedulerId(TabId::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageActivateTrailEdge";
	}

	std::wstring getFullName() const
	{
		std::wstring name = Edge::getReadableTypeString(type) + L":";
		name += sourceNameHierarchy.getQualifiedNameWithSignature() + L"->";
		name += targetNameHierarchy.getQualifiedNameWithSignature();
		return name;
	}

	virtual void print(std::wostream& os) const
	{
		for (Id edgeId: edgeIds)
		{
			os << edgeId << L",";
		}
		os << L" - " << getFullName();
	}

	const std::vector<Id> edgeIds;
	const Edge::EdgeType type;
	const NameHierarchy sourceNameHierarchy;
	const NameHierarchy targetNameHierarchy;
};

#endif	  // MESSAGE_ACTIVATE_TRAIL_EDGE_H
