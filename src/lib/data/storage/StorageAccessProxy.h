#pragma once

#include "FileInfo.h"
#include "FilePath.h"
#include "StorageAccess.h"

class StorageAccessProxy : public StorageAccess {
public:
  StorageAccessProxy();

  void setSubject(std::weak_ptr<StorageAccess> subject);

  // StorageAccess implementation
  Id getNodeIdForFileNode(const utility::file::FilePath& filePath) const override;
  Id getNodeIdForNameHierarchy(const NameHierarchy& nameHierarchy) const override;
  std::vector<Id> getNodeIdsForNameHierarchies(
      const std::vector<NameHierarchy> nameHierarchies) const override;

  NameHierarchy getNameHierarchyForNodeId(Id id) const override;
  std::vector<NameHierarchy> getNameHierarchiesForNodeIds(const std::vector<Id>& nodeIds) const override;
  std::map<Id, std::pair<Id, NameHierarchy>> getNodeIdToParentFileMap(
      const std::vector<Id>& nodeIds) const override;

  NodeType getNodeTypeForNodeWithId(Id id) const override;

  StorageEdge getEdgeById(Id edgeId) const override;

  std::shared_ptr<SourceLocationCollection> getFullTextSearchLocations(
      const std::wstring& searchTerm, bool caseSensitive) const override;
  std::vector<SearchMatch> getAutocompletionMatches(const std::wstring& query,
                                                    NodeTypeSet acceptedNodeTypes,
                                                    bool acceptCommands) const override;
  std::vector<SearchMatch> getSearchMatchesForTokenIds(const std::vector<Id>& tokenIds) const override;

  std::shared_ptr<Graph> getGraphForAll() const override;
  std::shared_ptr<Graph> getGraphForNodeTypes(NodeTypeSet nodeTypes) const override;
  std::shared_ptr<Graph> getGraphForActiveTokenIds(const std::vector<Id>& tokenIds,
                                                   const std::vector<Id>& expandedNodeIds,
                                                   bool* isActiveNamespace = nullptr) const override;
  std::shared_ptr<Graph> getGraphForChildrenOfNodeId(Id nodeId) const override;
  std::shared_ptr<Graph> getGraphForTrail(Id originId,
                                          Id targetId,
                                          NodeKindMask nodeTypes,
                                          Edge::TypeMask edgeTypes,
                                          bool nodeNonIndexed,
                                          size_t depth,
                                          bool directed) const override;

  NodeKindMask getAvailableNodeTypes() const override;
  Edge::TypeMask getAvailableEdgeTypes() const override;

  std::vector<Id> getActiveTokenIdsForId(Id tokenId, Id* declarationId) const override;
  std::vector<Id> getNodeIdsForLocationIds(const std::vector<Id>& locationIds) const override;

  std::shared_ptr<SourceLocationCollection> getSourceLocationsForTokenIds(
      const std::vector<Id>& tokenIds) const override;
  std::shared_ptr<SourceLocationCollection> getSourceLocationsForLocationIds(
      const std::vector<Id>& locationIds) const override;

  std::shared_ptr<SourceLocationFile> getSourceLocationsForFile(const utility::file::FilePath& filePath) const override;
  std::shared_ptr<SourceLocationFile> getSourceLocationsForLinesInFile(const utility::file::FilePath& filePath,
                                                                       size_t startLine,
                                                                       size_t endLine) const override;
  std::shared_ptr<SourceLocationFile> getSourceLocationsOfTypeInFile(const utility::file::FilePath& filePath,
                                                                     LocationType type) const override;

  std::shared_ptr<TextAccess> getFileContent(const utility::file::FilePath& filePath,
                                             bool showsErrors) const override;

  utility::file::FileInfo getFileInfoForFileId(Id id) const override;

  utility::file::FileInfo getFileInfoForFilePath(const utility::file::FilePath& filePath) const override;
  std::vector<utility::file::FileInfo> getFileInfosForFilePaths(const std::vector<utility::file::FilePath>& filePaths) const override;

  StorageStats getStorageStats() const override;

  ErrorCountInfo getErrorCount() const override;
  std::vector<ErrorInfo> getErrorsLimited(const ErrorFilter& filter) const override;
  std::vector<ErrorInfo> getErrorsForFileLimited(const ErrorFilter& filter,
                                                 const utility::file::FilePath& filePath) const override;
  std::shared_ptr<SourceLocationCollection> getErrorSourceLocations(
      const std::vector<ErrorInfo>& errors) const override;

  // TODO: remove these from access because it's not a getter!
  Id addNodeBookmark(const NodeBookmark& bookmark) override;
  Id addEdgeBookmark(const EdgeBookmark& bookmark) override;
  Id addBookmarkCategory(const std::wstring& categoryName) override;

  void updateBookmark(const Id bookmarkId,
                      const std::wstring& name,
                      const std::wstring& comment,
                      const std::wstring& categoryName) override;
  void removeBookmark(const Id id) override;
  void removeBookmarkCategory(const Id id) override;
  // END TODO

  std::vector<NodeBookmark> getAllNodeBookmarks() const override;
  std::vector<EdgeBookmark> getAllEdgeBookmarks() const override;
  std::vector<BookmarkCategory> getAllBookmarkCategories() const override;

  TooltipInfo getTooltipInfoForTokenIds(const std::vector<Id>& tokenIds,
                                        TooltipOrigin origin) const override;
  TooltipInfo getTooltipInfoForSourceLocationIdsAndLocalSymbolIds(
      const std::vector<Id>& locationIds, const std::vector<Id>& localSymbolIds) const override;

private:
  std::weak_ptr<StorageAccess> m_subject;
};