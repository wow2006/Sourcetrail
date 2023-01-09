#ifndef QT_ICON_BUTTON_H
#define QT_ICON_BUTTON_H

#include <QPushButton>

#include "FilePath.h"

class QtIconButton: public QPushButton
{
	Q_OBJECT
public:
	QtIconButton(const utility::file::FilePath& iconPath, const utility::file::FilePath& hoveredIconPath, QWidget* parent = nullptr);
	~QtIconButton() = default;

	void setColor(QColor color);

protected:
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);

private:
	void setIconFromPath(const utility::file::FilePath& path);

	const utility::file::FilePath m_iconPath;
	const utility::file::FilePath m_hoveredIconPath;

	QColor m_color;
};

#endif	  // QT_ICON_BUTTON_H
