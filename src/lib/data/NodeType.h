#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "FilePath.h"
#include "NodeKind.h"
#include "Tree.h"
#include "types.h"

class NodeType
{
public:
	enum StyleType
	{
		STYLE_PACKAGE = 0,
		STYLE_SMALL_NODE = 1,
		STYLE_BIG_NODE = 2,
		STYLE_GROUP = 3
	};

	struct BundleInfo
	{
		BundleInfo() {}

		BundleInfo(std::wstring bundleName)
			: m_nameMatcher([](const std::wstring&) { return true; }), m_bundleName(bundleName)
		{
		}

		BundleInfo(std::function<bool(std::wstring)> nameMatcher, std::wstring bundleName)
			: m_nameMatcher(nameMatcher), m_bundleName(bundleName)
		{
		}

		bool isValid() const
		{
			return m_bundleName.size() > 0;
		}

		std::function<bool(const std::wstring&)> m_nameMatcher = nullptr;
		std::wstring m_bundleName;
	};

	static std::vector<NodeType> getOverviewBundleNodeTypesOrdered();

	explicit NodeType(NodeKind kind);

	bool operator==(const NodeType& o) const;
	bool operator!=(const NodeType& o) const;
	bool operator<(const NodeType& o) const;

	NodeKind getKind() const;

	Id getId() const;
	bool isFile() const;
	bool isBuiltin() const;
	bool isUnknownSymbol() const;
	bool isInheritable() const;
	bool isPackage() const;
	bool isCallable() const;
	bool isVariable() const;
	bool isUsable() const;
	bool isPotentialMember() const;
	bool isCollapsible() const;
	bool isVisibleAsParentInGraph() const;
	bool hasSearchFilter() const;
	Tree<BundleInfo> getOverviewBundleTree() const;

	FilePath getIconPath() const;

	bool hasIcon() const;
	StyleType getNodeStyle() const;

	bool hasOverviewBundle() const;
	std::string getUnderscoredTypeString() const;
	std::string getReadableTypeString() const;
	std::wstring getUnderscoredTypeWString() const;
	std::wstring getReadableTypeWString() const;

	static std::vector<NodeType> const overviewBundleNodeTypesOrdered;

private:
	NodeKind m_kind;
};
