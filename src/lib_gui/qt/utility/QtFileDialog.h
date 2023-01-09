#ifndef QT_FILE_DIALOG_H
#define QT_FILE_DIALOG_H

namespace utility::file {
class FilePath;
} // namespace class utility::file
class QString;
class QStringList;
class QWidget;

class QtFileDialog
{
public:
	static QStringList getFileNamesAndDirectories(QWidget* parent, const utility::file::FilePath& path);

	static QString getExistingDirectory(QWidget* parent, const QString& caption, const utility::file::FilePath& dir);
	static QString getOpenFileName(
		QWidget* parent, const QString& caption, const utility::file::FilePath& dir, const QString& filter);

	static QString showSaveFileDialog(
		QWidget* parent, const QString& title, const utility::file::FilePath& directory, const QString& filter);

private:
	static QString getDir(QString dir);
	static void saveFilePickerLocation(const utility::file::FilePath& path);
};

#endif	  // QT_FILE_DIALOG_H
