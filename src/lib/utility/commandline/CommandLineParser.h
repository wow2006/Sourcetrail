#pragma once

#include <memory>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

class FilePath;
enum class RefreshMode;

namespace commandline {

class CommandLineParserImpl;

class CommandLineParser {
public:
	explicit CommandLineParser(std::string version);
	~CommandLineParser();

	CommandLineParser(const CommandLineParser&) = delete;
	CommandLineParser& operator=(const CommandLineParser&) = delete;
	CommandLineParser(CommandLineParser&&) = delete;
	CommandLineParser& operator=(CommandLineParser&&) = delete;

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

	const FilePath& getProjectFilePath() const;
	void setProjectFile(const FilePath& filepath);

	RefreshMode getRefreshMode() const;
	bool getShallowIndexingRequested() const;

private:
	std::unique_ptr<CommandLineParserImpl> m_pImpl;

};

}	 // namespace commandline
