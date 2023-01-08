#pragma once

#include "Bookmark.h"

class NodeBookmark : public Bookmark {
public:
  NodeBookmark(const Id id,
               const std::wstring& name,
               const std::wstring& comment,
               const TimeStamp& timeStamp,
               const BookmarkCategory& category);

  ~NodeBookmark() override;

  void addNodeId(const Id nodeId);
  void setNodeIds(const std::vector<Id>& nodeIds);
  std::vector<Id> getNodeIds() const;

private:
  std::vector<Id> m_nodeIds;
};