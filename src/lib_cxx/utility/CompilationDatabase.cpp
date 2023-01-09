#include "CompilationDatabase.h"

#include <set>

#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/JSONCompilationDatabase.h>

#include "FilePath.h"
#include "logging.h"
#include "utility.h"
#include "utilityString.h"

utility::CompilationDatabase::CompilationDatabase(const utility::file::FilePath& filePath): m_filePath(filePath)
{
	init();
}

std::vector<utility::file::FilePath> utility::CompilationDatabase::getAllHeaderPaths() const
{
	std::vector<utility::file::FilePath> paths = utility::concat(m_headers, m_systemHeaders);
	paths = utility::unique(paths);
	return paths;
}

std::vector<utility::file::FilePath> utility::CompilationDatabase::getHeaderPaths() const
{
	return m_headers;
}

std::vector<utility::file::FilePath> utility::CompilationDatabase::getSystemHeaderPaths() const
{
	return m_systemHeaders;
}

std::vector<utility::file::FilePath> utility::CompilationDatabase::getFrameworkHeaderPaths() const
{
	return m_frameworkHeaders;
}

void utility::CompilationDatabase::init()
{
	std::string error;
	std::shared_ptr<clang::tooling::JSONCompilationDatabase> cdb(
		clang::tooling::JSONCompilationDatabase::loadFromFile(
			utility::encodeToUtf8(m_filePath.wstr()),
			error,
			clang::tooling::JSONCommandLineSyntax::AutoDetect));

	if (!cdb)
	{
		LOG_ERROR(
			L"Loading compilation database from file \"" + m_filePath.wstr() +
			L"\" failed with error: " + utility::decodeFromUtf8(error));
		return;
	}

	std::vector<clang::tooling::CompileCommand> commands = cdb->getAllCompileCommands();
	std::set<utility::file::FilePath> frameworkHeaders;
	std::set<utility::file::FilePath> systemHeaders;
	std::set<utility::file::FilePath> headers;

	{
		const std::wstring frameworkIncludeFlag = L"-iframework";
		const std::wstring systemIncludeFlag = L"-isystem";
		const std::wstring quoteFlag = L"-iquote";
		const std::wstring includeFlag = L"-I";
		for (clang::tooling::CompileCommand& command: commands)
		{
			const std::wstring commandDirectory = utility::decodeFromUtf8(command.Directory);
			for (size_t i = 0; i < command.CommandLine.size(); i++)
			{
				std::wstring argument = utility::decodeFromUtf8(command.CommandLine[i]);
				if (i + 1 < command.CommandLine.size() &&
					!utility::isPrefix<std::string>("-", command.CommandLine[i + 1]))
				{
					argument += utility::decodeFromUtf8(command.CommandLine[++i]);
				}

				if (utility::isPrefix(frameworkIncludeFlag, argument))
				{
					frameworkHeaders.insert(
						utility::file::FilePath(
							utility::trim(argument.substr(frameworkIncludeFlag.size())),
							commandDirectory)
							.makeCanonical());
				}
				else if (utility::isPrefix(systemIncludeFlag, argument))
				{
					systemHeaders.insert(utility::file::FilePath(
											 utility::trim(argument.substr(systemIncludeFlag.size())),
											 commandDirectory)
											 .makeCanonical());
				}
				else if (utility::isPrefix(quoteFlag, argument))
				{
					headers.insert(
						utility::file::FilePath(utility::trim(argument.substr(quoteFlag.size())), commandDirectory)
							.makeCanonical());
				}
				else if (utility::isPrefix(includeFlag, argument))
				{
					headers.insert(
						utility::file::FilePath(utility::trim(argument.substr(includeFlag.size())), commandDirectory)
							.makeCanonical());
				}
			}
		}
	}

	m_headers = utility::toVector(headers);
	m_frameworkHeaders = utility::toVector(frameworkHeaders);
	m_systemHeaders = utility::toVector(systemHeaders);
}
