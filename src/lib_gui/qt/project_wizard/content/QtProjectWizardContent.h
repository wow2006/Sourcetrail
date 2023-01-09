#ifndef QT_PROJECT_WIZARD_CONTENT_H
#define QT_PROJECT_WIZARD_CONTENT_H

#include <QGridLayout>
#include <QLabel>
#include <QToolButton>
#include <QWidget>

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "QtHelpButton.h"
#include "QtProjectWizardWindow.h"
#include "QtThreadedFunctor.h"

class QtTextEditDialog;

class QtProjectWizardContent: public QWidget
{
	Q_OBJECT

public:
	QtProjectWizardContent(QtProjectWizardWindow* window);

	virtual void populate(QGridLayout* layout, int& row);
	virtual void windowReady();

	virtual void load();
	virtual void save();
	virtual void refresh();
	virtual bool check();

	virtual std::vector<utility::file::FilePath> getFilePaths() const;
	virtual QString getFileNamesTitle() const;
	virtual QString getFileNamesDescription() const;

	bool isRequired() const;
	void setIsRequired(bool isRequired);

protected:
	QLabel* createFormTitle(const QString& name) const;
	QLabel* createFormLabel(QString name) const;
	QLabel* createFormSubLabel(const QString& name) const;
	QToolButton* createSourceGroupButton(const QString& name, const QString& iconPath) const;

	QtHelpButton* addHelpButton(
		const QString& helpTitle, const QString& helpText, QGridLayout* layout, int row) const;
	QPushButton* addFilesButton(const QString& name, QGridLayout* layout, int row) const;
	QFrame* addSeparator(QGridLayout* layout, int row) const;

	QtProjectWizardWindow* m_window;

	QtTextEditDialog* m_filesDialog = nullptr;

protected slots:
	void filesButtonClicked();
	void closedFilesDialog();

private:
	void showFilesDialog(const std::vector<utility::file::FilePath>& filePaths);

	QtThreadedFunctor<const std::vector<utility::file::FilePath>&> m_showFilesFunctor;

	bool m_isRequired = false;
};

#endif	  // QT_PROJECT_WIZARD_CONTENT_H
