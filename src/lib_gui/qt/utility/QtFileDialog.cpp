#include "QtFileDialog.h"

#include <QFileDialog>
#include <QListView>
#include <QTreeView>

#include "ApplicationSettings.h"
#include "FilePath.h"
#include "QtFilesAndDirectoriesDialog.h"
#include "utilityApp.h"

QStringList QtFileDialog::getFileNamesAndDirectories(QWidget* parent, const utility::file::FilePath& path)
{
	const QString dir = getDir(
		QString::fromStdWString((path.isDirectory() ? path : path.getParentDirectory()).wstr()));

	QFileDialog* dialog =
		(utility::getOsType() == OS_MAC ? new QFileDialog(parent)
										: new QtFilesAndDirectoriesDialog(parent));

	if (!dir.isEmpty())
	{
		dialog->setDirectory(dir);
	}

	QListView* l = dialog->findChild<QListView*>(QStringLiteral("listView"));
	if (l)
	{
		l->setSelectionMode(QAbstractItemView::ExtendedSelection);
	}
	QTreeView* t = dialog->findChild<QTreeView*>();
	if (t)
	{
		t->setSelectionMode(QAbstractItemView::ExtendedSelection);
	}

	QStringList list;
	if (dialog->exec())
	{
		list = dialog->selectedFiles();
	}

	saveFilePickerLocation(utility::file::FilePath(dialog->directory().path().toStdString()));
	delete dialog;

	return list;
}

QString QtFileDialog::getExistingDirectory(QWidget* parent, const QString& caption, const utility::file::FilePath& dir)
{
	const QString dirPath = QFileDialog::getExistingDirectory(
		parent, caption, getDir(QString::fromStdWString(dir.wstr())));
	saveFilePickerLocation(utility::file::FilePath(dirPath.toStdString()));
	return dirPath;
}

QString QtFileDialog::getOpenFileName(
	QWidget* parent, const QString& caption, const utility::file::FilePath& dir, const QString& filter)
{
	const QString filePath = QFileDialog::getOpenFileName(
		parent, caption, getDir(QString::fromStdWString(dir.wstr())), filter);
	const utility::file::FilePath dirPath = utility::file::FilePath(filePath.toStdString()).getParentDirectory();
	saveFilePickerLocation(dirPath);
	return filePath;
}

QString QtFileDialog::showSaveFileDialog(
	QWidget* parent, const QString& title, const utility::file::FilePath& directory, const QString& filter)
{
#if defined(Q_OS_WIN) || defined(Q_OS_MAC)

	return QFileDialog::getSaveFileName(
		parent, title, getDir(QString::fromStdWString(directory.wstr())), filter);

#else
	QFileDialog dialog(parent, title, getDir(QString::fromStdWString(directory.wstr())), filter);

	if (parent)
	{
		dialog.setWindowModality(Qt::WindowModal);
	}

	QRegExp filter_regex(QStringLiteral("(?:^\\*\\.(?!.*\\()|\\(\\*\\.)(\\w+)"));
	QStringList filters = filter.split(QStringLiteral(";;"));

	if (!filters.isEmpty())
	{
		dialog.setNameFilters(filters);
	}

	dialog.setAcceptMode(QFileDialog::AcceptSave);

	if (dialog.exec() == QDialog::Accepted)
	{
		QString file_name = dialog.selectedFiles().constFirst();
		QFileInfo info(file_name);

		if (info.suffix().isEmpty() && !dialog.selectedNameFilter().isEmpty())
		{
			if (filter_regex.indexIn(dialog.selectedNameFilter()) != -1)
			{
				QString extension = filter_regex.cap(1);
				file_name += QStringLiteral(".") + extension;
			}
		}
		return file_name;
	}
	else
	{
		return QString();
	}
#endif	  // Q_OS_MAC || Q_OS_WIN
}

QString QtFileDialog::getDir(QString dir)
{
	if (!dir.isEmpty())
	{
		return dir;
	}

	dir = QString::fromStdString(
		ApplicationSettings::getInstance()->getLastFilepickerLocation().str());

	if (dir.isEmpty())	  // first app launch, settings file absent
	{
		dir = QDir::homePath();
	}

	return dir;
}

void QtFileDialog::saveFilePickerLocation(const utility::file::FilePath& path)
{
	if (!path.empty())
	{
		std::shared_ptr<ApplicationSettings> settings = ApplicationSettings::getInstance();
		settings->setLastFilepickerLocation(path);
		settings->save();
	}
}
