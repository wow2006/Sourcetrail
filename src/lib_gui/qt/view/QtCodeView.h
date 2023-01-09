#ifndef QT_CODE_VIEW_H
#define QT_CODE_VIEW_H

#include "CodeView.h"
#include "QtThreadedFunctor.h"

class QtCodeNavigator;

class QtCodeView: public CodeView
{
public:
	QtCodeView(ViewLayout* viewLayout);
	~QtCodeView() = default;

	// View implementation
	void createWidgetWrapper() override;
	void refreshView() override;

	// ScreenSearchResponder implementation
	bool isVisible() const override;
	void findMatches(ScreenSearchSender* sender, const std::wstring& query) override;
	void activateMatch(size_t matchIndex) override;
	void deactivateMatch(size_t matchIndex) override;
	void clearMatches() override;

	// CodeView implementation
	void clear() override;

	void showSnippets(
		const std::vector<CodeFileParams>& files,
		const CodeParams& params,
		const CodeScrollParams& scrollParams) override;

	void showSingleFile(
		const CodeFileParams& file,
		const CodeParams& params,
		const CodeScrollParams& scrollParams) override;

	void updateSourceLocations(const std::vector<CodeFileParams>& files) override;

	void scrollTo(const CodeScrollParams& params, bool animated) override;

	bool showsErrors() const override;

	void coFocusTokenIds(const std::vector<Id>& coFocusedTokenIds) override;
	void deCoFocusTokenIds() override;

	bool isInListMode() const override;
	void setMode(bool listMode) override;

	bool hasSingleFileCached(const utility::file::FilePath& filePath) const override;

	void setNavigationFocus(bool focus) override;
	bool hasNavigationFocus() const override;

private:
	void setNavigationState(const CodeParams& params);

	// void performScroll(const CodeScrollParams& scrollParams);
	void setStyleSheet() const;

	QtThreadedLambdaFunctor m_onQtThread;

	QtCodeNavigator* m_widget;

	bool m_hasFocus = false;
};

#endif	  // QT_CODE_VIEW_H
