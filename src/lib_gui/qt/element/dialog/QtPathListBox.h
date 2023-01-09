#ifndef QT_PATH_LIST_BOX_H
#define QT_PATH_LIST_BOX_H

#include "QtListBox.h"
#include "FilePath.h"

class QtPathListBox: public QtListBox
{
public:
	enum SelectionPolicyType
	{
		SELECTION_POLICY_FILES_ONLY,
		SELECTION_POLICY_DIRECTORIES_ONLY,
		SELECTION_POLICY_FILES_AND_DIRECTORIES
	};

	QtPathListBox(QWidget* parent, const QString& listName, SelectionPolicyType selectionPolicy);

	SelectionPolicyType getSelectionPolicy() const;

	const utility::file::FilePath& getRelativeRootDirectory() const;
	void setRelativeRootDirectory(const utility::file::FilePath& dir);

	std::vector<utility::file::FilePath> getPathsAsDisplayed() const;
	std::vector<utility::file::FilePath> getPathsAsAbsolute() const;

	void setPaths(const std::vector<utility::file::FilePath>& list, bool readOnly = false);
	void addPaths(const std::vector<utility::file::FilePath>& list, bool readOnly = false);

	void makeAbsolute(utility::file::FilePath& path) const;
	void makeRelativeIfShorter(utility::file::FilePath& path) const;

protected:
	void dropEvent(QDropEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;

private:
	virtual QtListBoxItem* createListBoxItem(QListWidgetItem* item) override;

	const SelectionPolicyType m_selectionPolicy;
	utility::file::FilePath m_relativeRootDirectory;
};

#endif	  // QT_PATH_LIST_BOX_H
