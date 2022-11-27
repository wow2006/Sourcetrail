#include "CommandLineParser.h"

#include <iostream>
#include <utility>

#include <boost/program_options.hpp>

#include "CommandlineCommandConfig.h"
#include "CommandlineCommandIndex.h"
#include "CommandlineHelper.h"
#include "ConfigManager.h"
#include "FilePath.h"
#include "RefreshInfo.h"
#include "TextAccess.h"
#include "utilityString.h"

namespace po = boost::program_options;

namespace commandline
{

class CommandLineParserImpl
{
public:
	CommandLineParserImpl(std::string version, CommandLineParser* pParent);
	~CommandLineParserImpl();

	CommandLineParserImpl(const CommandLineParserImpl&) = delete;
	CommandLineParserImpl& operator=(const CommandLineParserImpl&) = delete;
	CommandLineParserImpl(CommandLineParserImpl&&) = delete;
	CommandLineParserImpl& operator=(CommandLineParserImpl&&) = delete;

	void preparse(int argc, char** argv);
	void preparse(std::vector<std::string>& args);
	void parse();

	bool runWithoutGUI() const;
	bool exitApplication() const;

	bool hasError() const;
	std::wstring getError();

	void fullRefresh();
	void incompleteRefresh();
	void setShallowIndexingRequested(bool enabled = true);

	FilePath getProjectFilePath() const;
	void setProjectFile(const FilePath& filepath);

	RefreshMode getRefreshMode() const;
	bool getShallowIndexingRequested() const;

private:
	void processProjectfile();
	void printHelp() const;

private:
	CommandLineParser *m_pParent;
	boost::program_options::options_description m_options;
	boost::program_options::positional_options_description m_positional;

	std::vector<std::shared_ptr<CommandlineCommand>> m_commands;
	std::vector<std::string> m_args;

	const std::string m_version;
	FilePath m_projectFile;
	RefreshMode m_refreshMode = RefreshMode::REFRESH_UPDATED_FILES;
	bool m_shallowIndexingRequested = false;

	bool m_quit = false;
	bool m_withoutGUI = false;

	std::wstring m_errorString;
};

CommandLineParserImpl::CommandLineParserImpl(std::string version, CommandLineParser* pParent): m_pParent(pParent), m_version(std::move(version))
{
	po::options_description options("Options");
	options.add_options()("help,h", "Print this help message")(
		"version,v", "Version of Sourcetrail")(
		"project-file", po::value<std::string>(), "Open Sourcetrail with this project (.srctrlprj)");

	m_options.add(options);
	m_positional.add("project-file", 1);

	m_commands.push_back(std::make_unique<commandline::CommandlineCommandConfig>(m_pParent));
	m_commands.push_back(std::make_unique<commandline::CommandlineCommandIndex>(m_pParent));

	for (auto& command: m_commands)
	{
		command->setup();
	}
}

CommandLineParserImpl::~CommandLineParserImpl() = default;

void CommandLineParserImpl::preparse(int argc, char** argv)
{
	std::vector<std::string> args;
	for (int i = 1; i < argc; i++)
	{
		args.push_back(std::string(argv[i]));
	}

	preparse(args);
}

void CommandLineParserImpl::preparse(std::vector<std::string>& args)
{
	if (args.empty())
	{
		return;
	}

	m_args = args;

	try
	{
		for (auto& command: m_commands)
		{
			if (m_args[0] == command->name())
			{
				m_withoutGUI = true;
				return;
			}
		}

		po::variables_map variablesMap;
		po::positional_options_description positional;
		positional.add("project-file", 1);
		po::store(
			po::command_line_parser(m_args)
				.options(m_options)
				.positional(positional)
				.allow_unregistered()
				.run(),
			variablesMap);
		po::notify(variablesMap);

		if (variablesMap.find("version") != variablesMap.end())
		{
			std::cout << "Sourcetrail Version " << m_version << std::endl;
			m_quit = true;
			return;
		}

		if (variablesMap.find("help") != variablesMap.end())
		{
			printHelp();
			m_quit = true;
		}

		if (variablesMap.find("project-file") != variablesMap.end())
		{
			m_projectFile = FilePath(variablesMap["project-file"].as<std::string>());
			processProjectfile();
		}
	}
	catch (boost::program_options::error& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
		std::cerr << m_options << std::endl;
	}
}

void CommandLineParserImpl::parse()
{
	if (m_args.size() < 1)
	{
		return;
	}

	try
	{
		// parsing for all commands
		for (auto& command: m_commands)
		{
			if (m_args[0] == command->name())
			{
				m_args.erase(m_args.begin());
				CommandlineCommand::ReturnStatus status = command->parse(m_args);

				if (status != CommandlineCommand::ReturnStatus::CMD_OK)
				{
					m_quit = true;
				}
			}
		}
	}
	catch (boost::program_options::error& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
		std::cerr << m_options << std::endl;
	}
}

void CommandLineParserImpl::setProjectFile(const FilePath& filepath)
{
	m_projectFile = filepath;
	processProjectfile();
}

void CommandLineParserImpl::printHelp() const
{
	std::cout << "Usage:\n  Sourcetrail [command] [option...] [positional arguments]\n\n";

	// Commands
	std::cout << "Commands:\n";
	for (auto& command: m_commands)
	{
		std::cout << "  " << command->name();
		std::cout << std::string(std::max(23 - command->name().size(), size_t(2)), ' ');
		std::cout << command->description() << (command->hasHelp() ? "*" : "") << "\n";
	}
	std::cout << "\n  * has its own --help\n";

	std::cout << m_options << std::endl;

	if (m_positional.max_total_count() > 0)
	{
		std::cout << "Positional Arguments: ";
		for (unsigned int i = 0; i < m_positional.max_total_count(); i++)
		{
			std::cout << "\n  " << i + 1 << ": " << m_positional.name_for_position(i);
		}
		std::cout << std::endl;
	}
}

bool CommandLineParserImpl::runWithoutGUI() const
{
	return m_withoutGUI;
}

bool CommandLineParserImpl::exitApplication() const
{
	return m_quit;
}

bool CommandLineParserImpl::hasError() const
{
	return !m_errorString.empty();
}

std::wstring CommandLineParserImpl::getError()
{
	return m_errorString;
}

void CommandLineParserImpl::processProjectfile()
{
	m_projectFile.makeAbsolute();

	const std::wstring errorstring =
		L"Provided Projectfile is not valid:\n* Provided Projectfile('" + m_projectFile.fileName() +
		L"') ";
	if (!m_projectFile.exists())
	{
		m_errorString = errorstring + L" does not exist";
		m_projectFile = FilePath();
		return;
	}

	if (m_projectFile.extension() != L".srctrlprj")
	{
		m_errorString = errorstring + L" has a wrong file ending";
		m_projectFile = FilePath();
		return;
	}

	std::shared_ptr<ConfigManager> configManager = ConfigManager::createEmpty();
	if (!configManager->load(TextAccess::createFromFile(m_projectFile)))
	{
		m_errorString = errorstring + L" could not be loaded (invalid)";
		m_projectFile = FilePath();
		return;
	}
}

void CommandLineParserImpl::fullRefresh()
{
	m_refreshMode = RefreshMode::REFRESH_ALL_FILES;
}

void CommandLineParserImpl::incompleteRefresh()
{
	m_refreshMode = RefreshMode::REFRESH_UPDATED_AND_INCOMPLETE_FILES;
}

void CommandLineParserImpl::setShallowIndexingRequested(bool enabled)
{
	m_shallowIndexingRequested = enabled;
}

FilePath CommandLineParserImpl::getProjectFilePath() const
{
	return m_projectFile;
}

RefreshMode CommandLineParserImpl::getRefreshMode() const
{
	return m_refreshMode;
}

bool CommandLineParserImpl::getShallowIndexingRequested() const
{
	return m_shallowIndexingRequested;
}

CommandLineParser::CommandLineParser(std::string version) : m_pImpl(std::make_unique<CommandLineParserImpl>(std::move(version), this)) {}

CommandLineParser::~CommandLineParser() = default;

void CommandLineParser::preparse(int argc, char** argv) { m_pImpl->preparse(argc, argv); }

void CommandLineParser::preparse(std::vector<std::string>& args) { m_pImpl->preparse(args); }

void CommandLineParser::parse() { m_pImpl->parse(); }

bool CommandLineParser::runWithoutGUI() const { return m_pImpl->runWithoutGUI(); }

bool CommandLineParser::exitApplication() const { return m_pImpl->exitApplication(); }

bool CommandLineParser::hasError() const { return m_pImpl->hasError(); }

std::wstring CommandLineParser::getError() { return m_pImpl->getError(); }

void CommandLineParser::fullRefresh() { m_pImpl->fullRefresh(); }

void CommandLineParser::incompleteRefresh() { m_pImpl->incompleteRefresh(); }

void CommandLineParser::setShallowIndexingRequested(bool enabled) { m_pImpl->setShallowIndexingRequested(enabled); }

FilePath CommandLineParser::getProjectFilePath() const { return m_pImpl->getProjectFilePath(); }

void CommandLineParser::setProjectFile(const FilePath& filepath) { return m_pImpl->setProjectFile(filepath); }

RefreshMode CommandLineParser::getRefreshMode() const { return m_pImpl->getRefreshMode(); }

bool CommandLineParser::getShallowIndexingRequested() const { return m_pImpl->getShallowIndexingRequested(); }

}	 // namespace commandline
