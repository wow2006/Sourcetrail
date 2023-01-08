#pragma once

#include "Bookmark.h"

class EdgeBookmark : public Bookmark {
public:
  EdgeBookmark(const Id id,
               const std::wstring& name,
               const std::wstring& comment,
               const TimeStamp& timeStamp,
               const BookmarkCategory& category);

  ~EdgeBookmark() override;

  void addEdgeId(const Id edgeId);
  void setEdgeIds(const std::vector<Id>& edgesIds);
  std::vector<Id> getEdgeIds() const;

  void setActiveNodeId(const Id activeNodeId);
  Id getActiveNodeId() const;

private:
  std::vector<Id> m_edgeIds;
  Id m_activeNodeId;
};