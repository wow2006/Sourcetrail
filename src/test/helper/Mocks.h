// catch2
#include "catch.hpp"
// trompeloeil
#include "trompeloeil.hpp"
#include <memory>
// internal
#define TESTING
#include "Application.h"
#include "ConsoleLogger.h"
#include "MainView.h"
#include "SearchView.h"
#include "SharedMemoryGarbageCollector.h"
#include "Version.h"
#include "ViewFactory.h"
#include "BookmarkButtonsView.h"
#include "UndoRedoView.h"
#include "GraphView.h"
#include "CodeView.h"
#include "ViewLayout.h"
#include "ScreenSearchView.h"
#include "TabsView.h"

using namespace trompeloeil;

struct MainViewMocked : public MainView {
  MainViewMocked(const ViewFactory* viewFactory, StorageAccess* storageAccess)
      : MainView(viewFactory, storageAccess) {}

  MainViewMocked(const MainViewMocked&) = default;

  MAKE_MOCK0(loadLayout, void(), override);

  MAKE_MOCK0(saveLayout, void(), override);

  MAKE_MOCK0(refreshView, void(), override);

  MAKE_MOCK1(refreshUIState, void(bool isAfterIndexing), override);

  MAKE_MOCK1(loadWindow, void(bool showStartWindow), override);

  MAKE_MOCK0(hideStartScreen, void(), override);

  MAKE_MOCK1(setTitle, void(const std::wstring& title), override);

  MAKE_MOCK0(activateWindow, void(), override);

  MAKE_MOCK0(updateRecentProjectMenu, void(), override);

  MAKE_MOCK1(updateHistoryMenu, void(std::shared_ptr<MessageBase> message), override);

  MAKE_MOCK0(clearHistoryMenu, void(), override);

  MAKE_MOCK1(updateBookmarksMenu,
             void(const std::vector<std::shared_ptr<Bookmark>>& bookmarks),
             override);

  MAKE_MOCK0(clearBookmarksMenu, void(), override);

  // ViewLayout
  MAKE_MOCK1(addView, void(View* view), override);

  MAKE_MOCK1(overrideView, void(View* view), override);

  MAKE_MOCK1(removeView, void(View* view), override);

  MAKE_MOCK1(showView, void(View* view), override);

  MAKE_MOCK1(hideView, void(View* view), override);

  MAKE_MOCK2(setViewEnabled, void(View* view, bool enabled), override);
};

struct MockedViewFactory : public ViewFactory {
  using MainViewPtr = std::shared_ptr<MainView>;
  MAKE_CONST_MOCK1(createMainView, MainViewPtr(StorageAccess* storageAccess), override);
  using CompositeViewPtr = std::shared_ptr<CompositeView>;
  MAKE_CONST_MOCK4(createCompositeView,
                   CompositeViewPtr(ViewLayout* viewLayout,
                                    CompositeView::CompositeDirection direction,
                                    const std::string& name,
                                    const Id tabId),
                   override);
  using TabbedViewPtr = std::shared_ptr<TabbedView>;
  MAKE_CONST_MOCK2(createTabbedView,
                   TabbedViewPtr(ViewLayout* viewLayout, const std::string& name),
                   override);
  using BookmarkButtonsViewPtr = std::shared_ptr<BookmarkButtonsView>;
  MAKE_CONST_MOCK1(createBookmarkButtonsView, BookmarkButtonsViewPtr(ViewLayout* viewLayout), override);
  using BookmarkViewPtr = std::shared_ptr<BookmarkView>;
  MAKE_CONST_MOCK1(createBookmarkView, BookmarkViewPtr(ViewLayout* viewLayout), override);
  using CodeViewPtr = std::shared_ptr<CodeView>;
  MAKE_CONST_MOCK1(createCodeView, CodeViewPtr(ViewLayout* viewLayout), override);
  using CustomTrailViewPtr = std::shared_ptr<CustomTrailView>;
  MAKE_CONST_MOCK1(createCustomTrailView, CustomTrailViewPtr(ViewLayout* viewLayout), override);
  using ErrorViewPtr = std::shared_ptr<ErrorView>;
  MAKE_CONST_MOCK1(createErrorView, ErrorViewPtr(ViewLayout* viewLayout), override);
  using GraphViewPtr = std::shared_ptr<GraphView>;
  MAKE_CONST_MOCK1(createGraphView, GraphViewPtr(ViewLayout* viewLayout), override);
  using RefreshViewPtr = std::shared_ptr<RefreshView>;
  MAKE_CONST_MOCK1(createRefreshView, RefreshViewPtr(ViewLayout* viewLayout), override);
  using ScreenSearchViewPtr = std::shared_ptr<ScreenSearchView>;
  MAKE_CONST_MOCK1(createScreenSearchView, ScreenSearchViewPtr(ViewLayout* viewLayout), override);
  using SearchViewPtr = std::shared_ptr<SearchView>;
  MAKE_CONST_MOCK1(createSearchView, SearchViewPtr(ViewLayout* viewLayout), override);
  using StatusBarViewPtr = std::shared_ptr<StatusBarView>;
  MAKE_CONST_MOCK1(createStatusBarView, StatusBarViewPtr(ViewLayout* viewLayout), override);
  using StatusViewPtr = std::shared_ptr<StatusView>;
  MAKE_CONST_MOCK1(createStatusView, StatusViewPtr(ViewLayout* viewLayout), override);
  using TabsViewPtr = std::shared_ptr<TabsView>;
  MAKE_CONST_MOCK1(createTabsView, TabsViewPtr(ViewLayout* viewLayout), override);
  using TooltipView = std::shared_ptr<TooltipView>;
  MAKE_CONST_MOCK1(createTooltipView, TooltipView(ViewLayout* viewLayout), override);
  using UndoRedoViewPtr = std::shared_ptr<UndoRedoView>;
  MAKE_CONST_MOCK1(createUndoRedoView, UndoRedoViewPtr(ViewLayout* viewLayout), override);
  using DialogViewPtr = std::shared_ptr<DialogView>;
  MAKE_CONST_MOCK3(createDialogView,
                   DialogViewPtr(ViewLayout* viewLayout,
                                 DialogView::UseCase useCase,
                                 StorageAccess* storageAccess),
                   override);
  using GraphViewStyleImplPtr = std::shared_ptr<GraphViewStyleImpl>;
  MAKE_CONST_MOCK0(createGraphStyleImpl, GraphViewStyleImplPtr(), override);
};

struct MockedSearchView : public SearchView {
  MockedSearchView(ViewLayout* pLayout) : SearchView(pLayout) {}
  MAKE_CONST_MOCK0(getQuery, std::wstring(), override);
  using SearchMatchVec = std::vector<SearchMatch>;
  MAKE_MOCK1(setMatches, void(const SearchMatchVec&), override);
  MAKE_MOCK0(setFocus, void(), override);
  MAKE_MOCK0(findFulltext, void(), override);
  MAKE_MOCK1(setAutocompletionList, void(const SearchMatchVec&), override);
  MAKE_MOCK0(createWidgetWrapper, void(), override);
  MAKE_MOCK0(refreshView, void(), override);
};

struct MockedUndoRedoView : public UndoRedoView {
  MockedUndoRedoView(ViewLayout* pLayout) : UndoRedoView(pLayout) {}
  ~MockedUndoRedoView() override = default;
  MAKE_MOCK1(setRedoButtonEnabled, void(bool), override);
  MAKE_MOCK1(setUndoButtonEnabled, void(bool), override);
  using SearchMatchVec = std::vector<SearchMatch>;
  MAKE_MOCK2(updateHistory, void(const SearchMatchVec&, size_t), override);
  MAKE_MOCK0(createWidgetWrapper, void(), override);
  MAKE_MOCK0(refreshView, void(), override);
};

struct MockedBookmarkButtonsView : public BookmarkButtonsView {
  MockedBookmarkButtonsView(ViewLayout* pLayout) : BookmarkButtonsView(pLayout) {}
  ~MockedBookmarkButtonsView() override = default;
  MAKE_MOCK1(setCreateButtonState, void(const MessageBookmarkButtonState::ButtonState&), override);
  MAKE_MOCK0(createWidgetWrapper, void(), override);
  MAKE_MOCK0(refreshView, void(), override);
};

struct MockedGraphView : public GraphView {
  MockedGraphView(ViewLayout* pLayout) : GraphView(pLayout) {}
  ~MockedGraphView() override = default;
  using GraphPtr = std::shared_ptr<Graph>;
  using DummyNodePtrVec = std::vector<std::shared_ptr<DummyNode>>;
  using DummyEdgePtrVec = std::vector<std::shared_ptr<DummyEdge>>;
  MAKE_MOCK4(rebuildGraph, void(GraphPtr, const DummyNodePtrVec&, const DummyEdgePtrVec&, const GraphParams), override);
  MAKE_MOCK0(clear, void(), override);
  using IdVec = std::vector<Id>;
  MAKE_MOCK1(coFocusTokenIds, void(const IdVec&), override);
  MAKE_MOCK1(deCoFocusTokenIds, void(const IdVec&), override);
  MAKE_MOCK0(resizeView, void(), override);
  MAKE_CONST_MOCK0(getViewSize, Vec2i(), override);
  MAKE_CONST_MOCK0(getGrouping, GroupType(), override);
  MAKE_MOCK2(scrollToValues, void(int,int), override);
  MAKE_MOCK1(activateEdge, void(Id), override);
  MAKE_MOCK1(setNavigationFocus, void(bool), override);
  MAKE_CONST_MOCK0(hasNavigationFocus, bool(), override);
  MAKE_MOCK0(createWidgetWrapper, void(), override);
  MAKE_MOCK0(refreshView, void(), override);
  MAKE_CONST_MOCK0(isVisible, bool(), override);
  MAKE_MOCK2(findMatches, void(ScreenSearchSender*,const std::wstring&), override);
  MAKE_MOCK1(activateMatch, void(size_t), override);
  MAKE_MOCK1(deactivateMatch, void(size_t), override);
  MAKE_MOCK0(clearMatches, void(), override);
};

struct MockedCodeView : public CodeView {
  MockedCodeView(ViewLayout* pLayout) : CodeView(pLayout) {}
  ~MockedCodeView() override = default;
  MAKE_MOCK0(clear, void(), override);
  using CodeFileParamsVec = std::vector<CodeFileParams>;
  MAKE_MOCK3(showSnippets, void(const CodeFileParamsVec& files, const CodeParams& params, const CodeScrollParams& scrollParams), override);
  MAKE_MOCK3(showSingleFile, void(const CodeFileParams& files,
                                  const CodeParams& params,
                                  const CodeScrollParams& scrollParams), override);
  MAKE_MOCK1(updateSourceLocations, void(const CodeFileParamsVec&), override);
  MAKE_MOCK2(scrollTo, void(const CodeScrollParams&, bool), override);
  MAKE_CONST_MOCK0(showsErrors, bool(), override);
  using IdVec = std::vector<Id>;
  MAKE_MOCK1(coFocusTokenIds, void(const IdVec&), override);
  MAKE_MOCK0(deCoFocusTokenIds, void(), override);
  MAKE_CONST_MOCK0(isInListMode, bool(), override);
  MAKE_MOCK1(setMode, void(bool), override);
  MAKE_CONST_MOCK1(hasSingleFileCached, bool(const utility::file::FilePath& filePath), override);
  MAKE_MOCK1(setNavigationFocus, void(bool), override);
  MAKE_CONST_MOCK0(hasNavigationFocus, bool(), override);

  MAKE_MOCK0(createWidgetWrapper, void(), override);
  MAKE_MOCK0(refreshView, void(), override);
  MAKE_CONST_MOCK0(isVisible, bool(), override);
  MAKE_MOCK2(findMatches, void(ScreenSearchSender*, const std::wstring&), override);
  MAKE_MOCK1(activateMatch, void(size_t matchIndex), override);
  MAKE_MOCK1(deactivateMatch, void(size_t matchIndex), override);
  MAKE_MOCK0(clearMatches, void(), override);
};

struct MockedScreenSearchView : public ScreenSearchView {
  MockedScreenSearchView(ViewLayout* viewLayout) : ScreenSearchView(viewLayout) {}
  ~MockedScreenSearchView() override = default;
  MAKE_MOCK1(setMatchCount, void(size_t), override);
  MAKE_MOCK1(setMatchIndex, void(size_t), override);
  MAKE_MOCK1(addResponder, void(const std::string&), override);
  MAKE_MOCK0(createWidgetWrapper, void(), override);
  MAKE_MOCK0(refreshView, void(), override);
};

struct MockedTabsView : public TabsView {
  MockedTabsView(ViewLayout* viewLayout) : TabsView(viewLayout) {}
  ~MockedTabsView() override = default;
  MAKE_MOCK0(clear, void(), override);
  MAKE_MOCK2(openTab, void(bool, const SearchMatch&), override);
  MAKE_MOCK0(closeTab, void(), override);
  MAKE_MOCK1(destroyTab, void(Id), override);
  MAKE_MOCK1(selectTab, void(bool), override);
  using SearchMatchVec = std::vector<SearchMatch>;
  MAKE_MOCK2(updateTab, void(Id, const SearchMatchVec&), override);
  MAKE_MOCK0(createWidgetWrapper, void(), override);
  MAKE_MOCK0(refreshView, void(), override);
};