#include "SourceGroupJavaMaven.h"

#include "Application.h"
#include "ApplicationSettings.h"
#include "DialogView.h"
#include "FileSystem.h"
#include "MessageStatus.h"
#include "ScopedFunctor.h"
#include "SourceGroupSettingsJavaMaven.h"
#include "logging.h"
#include "utility.h"
#include "utilityJava.h"
#include "utilityMaven.h"

SourceGroupJavaMaven::SourceGroupJavaMaven(std::shared_ptr<SourceGroupSettingsJavaMaven> settings)
	: m_settings(settings)
	, m_allSourcePathsCache(std::bind(&SourceGroupJavaMaven::doGetAllSourcePaths, this))
{
}

bool SourceGroupJavaMaven::prepareIndexing()
{
	if (!utility::prepareJavaEnvironmentAndDisplayOccurringErrors())
	{
		return false;
	}

	if (!prepareMavenData())
	{
		return false;
	}

	return true;
}

std::vector<utility::file::FilePath> SourceGroupJavaMaven::getAllSourcePaths() const
{
	return m_allSourcePathsCache.getValue();
}

std::vector<utility::file::FilePath> SourceGroupJavaMaven::doGetClassPath() const
{
	std::vector<utility::file::FilePath> classPath = utility::getClassPath({}, true, getAllSourceFilePaths());

	if (m_settings && m_settings->getMavenDependenciesDirectoryPath().exists())
	{
		std::vector<utility::file::FilePath> mavenJarPaths = FileSystem::getFilePathsFromDirectory(
			m_settings->getMavenDependenciesDirectoryPath(), {L".jar"});

		for (const utility::file::FilePath& mavenJarPath: mavenJarPaths)
		{
			LOG_INFO(L"Adding jar to classpath: " + mavenJarPath.wstr());
		}

		utility::append(classPath, mavenJarPaths);
	}

	return classPath;
}

std::shared_ptr<SourceGroupSettings> SourceGroupJavaMaven::getSourceGroupSettings()
{
	return m_settings;
}

std::shared_ptr<const SourceGroupSettings> SourceGroupJavaMaven::getSourceGroupSettings() const
{
	return m_settings;
}

bool SourceGroupJavaMaven::prepareMavenData()
{
	if (m_settings && m_settings->getMavenProjectFilePathExpandedAndAbsolute().exists())
	{
		const utility::file::FilePath mavenPath = ApplicationSettings::getInstance()->getMavenPath();
		const utility::file::FilePath mavenSettingsPath = m_settings->getMavenSettingsFilePathExpandedAndAbsolute();
		const utility::file::FilePath projectRootPath =
			m_settings->getMavenProjectFilePathExpandedAndAbsolute().getParentDirectory();

		std::shared_ptr<DialogView> dialogView = lib::app::Application::getInstance()->getDialogView(
			DialogView::UseCase::PROJECT_SETUP);
		dialogView->showUnknownProgressDialog(
			L"Preparing Project", L"Maven\nGenerating Source Files");

		ScopedFunctor dialogHider([&dialogView]() { dialogView->hideUnknownProgressDialog(); });

		const std::wstring errorMessage = utility::mavenGenerateSources(
			mavenPath, mavenSettingsPath, projectRootPath);
		if (!errorMessage.empty())
		{
			MessageStatus(errorMessage, true, false).dispatch();
			lib::app::Application::getInstance()->handleDialog(errorMessage);
			return false;
		}

		dialogView->showUnknownProgressDialog(
			L"Preparing Project", L"Maven\nExporting Dependencies");

		bool success = utility::mavenCopyDependencies(
			mavenPath,
			mavenSettingsPath,
			projectRootPath,
			m_settings->getMavenDependenciesDirectoryPath());

		return success;
	}

	return true;
}

std::vector<utility::file::FilePath> SourceGroupJavaMaven::doGetAllSourcePaths() const
{
	std::vector<utility::file::FilePath> sourcePaths;
	if (m_settings && m_settings->getMavenProjectFilePathExpandedAndAbsolute().exists())
	{
		std::shared_ptr<DialogView> dialogView = lib::app::Application::getInstance()->getDialogView(
			DialogView::UseCase::PROJECT_SETUP);
		dialogView->showUnknownProgressDialog(
			L"Preparing Project", L"Maven\nFetching Source Directories");

		const utility::file::FilePath mavenPath(ApplicationSettings::getInstance()->getMavenPath());
		const utility::file::FilePath mavenSettingsPath = m_settings->getMavenSettingsFilePathExpandedAndAbsolute();
		const utility::file::FilePath projectRootPath =
			m_settings->getMavenProjectFilePathExpandedAndAbsolute().getParentDirectory();

		sourcePaths = utility::mavenGetAllDirectoriesFromEffectivePom(
			mavenPath,
			mavenSettingsPath,
			projectRootPath,
			m_settings->getMavenDependenciesDirectoryPath(),
			m_settings->getShouldIndexMavenTests());

		dialogView->hideUnknownProgressDialog();
	}
	return sourcePaths;
}
