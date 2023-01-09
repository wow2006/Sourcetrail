#include "utilityMaven.h"

#include <cstdlib>

#include "Application.h"
#include "ApplicationSettings.h"
#include "FilePath.h"
#include "MessageStatus.h"
#include "TextAccess.h"
#include "logging.h"
#include "utility.h"
#include "utilityApp.h"
#include "utilityJava.h"
#include "utilityString.h"
#include "utilityXml.h"

namespace
{
void fetchDirectories(
	std::vector<utility::file::FilePath>& pathList,
	std::shared_ptr<TextAccess> xmlAccess,
	const std::vector<std::string>& tags,
	const utility::file::FilePath& toAppend = utility::file::FilePath())
{
	{
		std::string tagString = "";
		for (size_t i = 0; i < tags.size(); i++)
		{
			if (i != 0)
			{
				tagString += " -> ";
			}
			tagString += tags[i];
		}
		LOG_INFO("Fetching source directories in \"" + tagString + "\".");
	}

	std::vector<std::string> fetchedDirectories = utility::getValuesOfAllXmlElementsOnPath(
		xmlAccess, tags);
	LOG_INFO("Found " + std::to_string(fetchedDirectories.size()) + " source directories.");

	for (const std::string& fetchedDirectory: fetchedDirectories)
	{
		utility::file::FilePath path(fetchedDirectory);
		if (!toAppend.empty())
		{
			path.concatenate(toAppend);
		}
		pathList.push_back(path);
		LOG_INFO(L"Found directory \"" + path.wstr() + L"\".");
	}
}

std::wstring getErrorMessageFromMavenOutput(std::shared_ptr<const TextAccess> mavenOutput)
{
	const std::string errorPrefix = "[ERROR]";
	const std::string fatalPrefix = "[FATAL]";

	std::wstring errorMessage;

	for (const std::string& line: mavenOutput->getAllLines())
	{
		const std::string trimmedLine = utility::trim(line);

		if (utility::isPrefix<std::string>(errorPrefix, trimmedLine))
		{
			errorMessage += utility::decodeFromUtf8(
				utility::trim(trimmedLine.substr(errorPrefix.size())) + "\n");
		}
		else if (utility::isPrefix<std::string>(fatalPrefix, trimmedLine))
		{
			errorMessage += utility::decodeFromUtf8(trimmedLine + "\n");
		}
	}

	if (!errorMessage.empty())
	{
		errorMessage = L"The following error occurred while executing a Maven command:\n\n" +
			errorMessage;
	}

	return errorMessage;
}

std::vector<std::wstring> getMavenArgs(const utility::file::FilePath& settingsFilePath)
{
	std::vector<std::wstring> args;
	if (!settingsFilePath.empty() && settingsFilePath.exists())
	{
		args.push_back(L"--settings \"" + settingsFilePath.wstr() + L"\"");
	}
	return args;
}

}	 // namespace

namespace utility
{
std::wstring mavenGenerateSources(
	const utility::file::FilePath& mavenPath, const utility::file::FilePath& settingsFilePath, const utility::file::FilePath& projectDirectoryPath)
{
	utility::setJavaHomeVariableIfNotExists();

	auto args = getMavenArgs(settingsFilePath);
	args.push_back(L"generate-sources");

	std::shared_ptr<TextAccess> outputAccess = TextAccess::createFromString(utility::encodeToUtf8(
		utility::executeProcess(mavenPath.wstr(), args, projectDirectoryPath, true, 60000).output));

	if (outputAccess->isEmpty())
	{
		return L"Sourcetrail was unable to locate Maven on this machine.\n"
			   "Please make sure to provide the correct Maven Path in the preferences.";
	}

	return getErrorMessageFromMavenOutput(outputAccess);
}

bool mavenCopyDependencies(
	const utility::file::FilePath& mavenPath,
	const utility::file::FilePath& settingsFilePath,
	const utility::file::FilePath& projectDirectoryPath,
	const utility::file::FilePath& outputDirectoryPath)
{
	utility::setJavaHomeVariableIfNotExists();

	auto args = getMavenArgs(settingsFilePath);
	args.push_back(L"dependency:copy-dependencies");
	args.push_back(L"-DoutputDirectory=" + outputDirectoryPath.wstr());

	std::shared_ptr<TextAccess> outputAccess = TextAccess::createFromString(utility::encodeToUtf8(
		utility::executeProcess(mavenPath.wstr(), args, projectDirectoryPath, true, 60000).output));

	const std::wstring errorMessage = getErrorMessageFromMavenOutput(outputAccess);
	if (!errorMessage.empty())
	{
		MessageStatus(errorMessage, true, false).dispatch();
		lib::app::Application::getInstance()->handleDialog(errorMessage);
		return false;
	}

	return !outputAccess->isEmpty();
}

std::vector<utility::file::FilePath> mavenGetAllDirectoriesFromEffectivePom(
	const utility::file::FilePath& mavenPath,
	const utility::file::FilePath& settingsFilePath,
	const utility::file::FilePath& projectDirectoryPath,
	const utility::file::FilePath& outputDirectoryPath,
	bool addTestDirectories)
{
	utility::setJavaHomeVariableIfNotExists();

	utility::file::FilePath outputPath = outputDirectoryPath.getConcatenated(utility::file::FilePath("/effective-pom.xml"));

	auto args = getMavenArgs(settingsFilePath);
	args.push_back(L"help:effective-pom");
	args.push_back(L"-Doutput=" + outputPath.wstr());

	std::shared_ptr<TextAccess> outputAccess = TextAccess::createFromString(utility::encodeToUtf8(
		utility::executeProcess(mavenPath.wstr(), args, projectDirectoryPath, true, 60000).output));

	const std::wstring errorMessage = getErrorMessageFromMavenOutput(outputAccess);
	if (!errorMessage.empty())
	{
		MessageStatus(errorMessage, true, false).dispatch();
		lib::app::Application::getInstance()->handleDialog(errorMessage);
		return {};
	}
	else if (!outputPath.exists())
	{
		LOG_ERROR("Maven effective-pom didn't generate an output file: " + outputPath.str());
		return {};
	}

	std::shared_ptr<TextAccess> xmlAccess = TextAccess::createFromFile(outputPath);

	std::vector<utility::file::FilePath> uncheckedDirectories;
	fetchDirectories(
		uncheckedDirectories,
		xmlAccess,
		utility::createVectorFromElements<std::string>("project", "build", "sourceDirectory"));
	fetchDirectories(
		uncheckedDirectories,
		xmlAccess,
		utility::createVectorFromElements<std::string>(
			"projects", "project", "build", "sourceDirectory"));
	fetchDirectories(
		uncheckedDirectories,
		xmlAccess,
		utility::createVectorFromElements<std::string>("project", "build", "directory"),
		utility::file::FilePath(L"generated-sources"));
	fetchDirectories(
		uncheckedDirectories,
		xmlAccess,
		utility::createVectorFromElements<std::string>("projects", "project", "build", "directory"),
		utility::file::FilePath(L"generated-sources"));

	if (addTestDirectories)
	{
		fetchDirectories(
			uncheckedDirectories,
			xmlAccess,
			utility::createVectorFromElements<std::string>(
				"project", "build", "testSourceDirectory"));
		fetchDirectories(
			uncheckedDirectories,
			xmlAccess,
			utility::createVectorFromElements<std::string>(
				"projects", "project", "build", "testSourceDirectory"));
		fetchDirectories(
			uncheckedDirectories,
			xmlAccess,
			utility::createVectorFromElements<std::string>("project", "build", "directory"),
			utility::file::FilePath(L"generated-test-sources"));
		fetchDirectories(
			uncheckedDirectories,
			xmlAccess,
			utility::createVectorFromElements<std::string>(
				"projects", "project", "build", "directory"),
			utility::file::FilePath(L"generated-test-sources"));
	}

	std::vector<utility::file::FilePath> directories;
	for (const utility::file::FilePath& uncheckedDirectory: uncheckedDirectories)
	{
		if (uncheckedDirectory.exists())
		{
			directories.push_back(uncheckedDirectory);
		}
	}

	LOG_INFO(
		"Found " + std::to_string(directories.size()) + " of " +
		std::to_string(uncheckedDirectories.size()) + " directories on system.");

	return directories;
}
}	 // namespace utility
