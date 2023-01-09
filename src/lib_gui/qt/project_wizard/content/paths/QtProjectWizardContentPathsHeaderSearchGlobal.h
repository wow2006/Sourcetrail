#ifndef QT_PROJECT_WIZARD_CONTENT_PATHS_HEADER_SEARCH_GLOBAL_H
#define QT_PROJECT_WIZARD_CONTENT_PATHS_HEADER_SEARCH_GLOBAL_H

#include "QtProjectWizardContentPaths.h"

class QtProjectWizardContentPathsHeaderSearchGlobal: public QtProjectWizardContentPaths
{
	Q_OBJECT
public:
	QtProjectWizardContentPathsHeaderSearchGlobal(QtProjectWizardWindow* window);

	// QtProjectWizardContent implementation
	virtual void load() override;
	virtual void save() override;

	virtual bool check() override;

protected:
	virtual void detectedPaths(const std::vector<utility::file::FilePath>& paths) override;

private:
	void setPaths(const std::vector<utility::file::FilePath>& paths);
};

#endif	  // QT_PROJECT_WIZARD_CONTENT_PATHS_HEADER_SEARCH_GLOBAL_H
