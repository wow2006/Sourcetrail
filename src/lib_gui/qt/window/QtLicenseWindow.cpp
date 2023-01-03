#include "QtLicenseWindow.h"

#include <QLabel>
#include <QVBoxLayout>

#include "licenses.h"

QtLicenseWindow::QtLicenseWindow(QWidget* parent): QtWindow(false, parent)
{
	setScrollAble(true);
}

QSize QtLicenseWindow::sizeHint() const
{
	return QSize(650, 600);
}

void QtLicenseWindow::populateWindow(QWidget* widget)
{
	QVBoxLayout* layout = new QVBoxLayout(widget);

	QLabel* licenseName = new QLabel();
	licenseName->setText(
		QString::fromLatin1(licenseApp.name) +
		QString::fromLatin1(
			std::string(licenseApp.version).empty()
				? ""
				: (std::string(" (v") + licenseApp.version + ")").c_str()));
	QFont _font = licenseName->font();
	_font.setPixelSize(36);
	_font.setBold(true);
	licenseName->setFont(_font);
	layout->addWidget(licenseName);

	QLabel* licenseURL = new QLabel();
	licenseURL->setText(
		QString::fromLatin1("<a href=\"%1\">%1</a>").arg(QString::fromLatin1(licenseApp.url)));
	licenseURL->setOpenExternalLinks(true);
	layout->addWidget(licenseURL);

	QLabel* licenseText = new QLabel();
	licenseText->setFixedWidth(550);
	licenseText->setWordWrap(true);
	licenseText->setText(QString::fromLatin1(licenseApp.license));
	layout->addWidget(licenseText);

	layout->addSpacing(30);

	QLabel* header3rdParties = new QLabel(QStringLiteral(
		"<b>Copyrights and Licenses for Third Party Software Distributed with Sourcetrail:</b><br "
		"/>"
		"Sourcetrail contains code written by the following third parties that have <br />"
		"additional or alternate copyrights, licenses, and/or restrictions:"));
	layout->addWidget(header3rdParties);

	layout->addSpacing(30);

	for (LicenseInfo license: licenses3rdParties)
	{
		QLabel* licenseNameLabel = new QLabel();
		licenseNameLabel->setText(
			QString::fromLatin1(license.name) +
			QString::fromLatin1(
				std::string(license.version).empty()
					? ""
					: (std::string(" (v") + license.version + ")").c_str()));
		licenseNameLabel->setFont(_font);
		layout->addWidget(licenseNameLabel);

		QLabel* licenseURLLabel = new QLabel();
		licenseURLLabel->setText(
			QString::fromLatin1("<a href=\"%1\">%1</a>").arg(QString::fromLatin1(license.url)));
		licenseURLLabel->setOpenExternalLinks(true);
		layout->addWidget(licenseURLLabel);

		QLabel* licenseText2 = new QLabel();
		licenseText2->setFixedWidth(550);
		licenseText2->setWordWrap(true);
		licenseText2->setText(QString::fromLatin1(license.license));
		layout->addWidget(licenseText2);

		layout->addSpacing(30);
	}

	widget->setLayout(layout);
}

void QtLicenseWindow::windowReady()
{
	updateTitle(QStringLiteral("License"));
	updateCloseButton(QStringLiteral("Close"));

	setNextVisible(false);
	setPreviousVisible(false);
}
