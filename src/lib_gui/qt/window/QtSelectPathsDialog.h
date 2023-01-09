#ifndef QT_SELECT_PATHS_DIALOG_H
#define QT_SELECT_PATHS_DIALOG_H

#include "QtTextEditDialog.h"

namespace utility::file {
class FilePath;
} // namespace class utility::file
class QListWidget;

class QtSelectPathsDialog: public QtTextEditDialog
{
	Q_OBJECT
public:
	QtSelectPathsDialog(const QString& title, const QString& description, QWidget* parent = 0);

	std::vector<utility::file::FilePath> getPathsList() const;
	void setPathsList(
		const std::vector<utility::file::FilePath>& paths,
		const std::vector<utility::file::FilePath>& checkedPaths,
		const utility::file::FilePath& rootPathForRelativePaths);

	virtual void populateWindow(QWidget* widget) override;
	virtual void windowReady() override;

private:
	QListWidget* m_list;

	void checkSelected(bool checked);
};

#endif	  // QT_SELECT_PATHS_DIALOG_H
