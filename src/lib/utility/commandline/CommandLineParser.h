#pragma once

#include <RefreshInfo.h>

#include <boost/program_options.hpp>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace commandline {

class CommandlineCommand;

class CommandLineParser {
 public:
  CommandLineParser(std::string version);
  ~CommandLineParser();

  CommandLineParser(const CommandLineParser&) = delete;
  CommandLineParser& operator=(const CommandLineParser&) = delete;
  CommandLineParser(CommandLineParser&&) = delete;
  CommandLineParser& operator=(CommandLineParser&&) = delete;

  void registerCommands(std::vector<std::shared_ptr<CommandlineCommand>> commands);

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

  std::filesystem::path getProjectFilePath() const;
  void setProjectFile(const std::filesystem::path& filepath);

  RefreshMode getRefreshMode() const;
  bool getShallowIndexingRequested() const;

 private:
  void printHelp() const;

 private:
  boost::program_options::options_description m_options;
  boost::program_options::positional_options_description m_positional;

  std::vector<std::shared_ptr<CommandlineCommand>> m_commands;
  std::vector<std::string> m_args;

  const std::string m_version;
  std::filesystem::path m_projectFile;
  RefreshMode m_refreshMode = RefreshMode::REFRESH_UPDATED_FILES;
  bool m_shallowIndexingRequested = false;

  bool m_quit = false;
  bool m_withoutGUI = false;

  std::wstring m_errorString;
};

}  // namespace commandline
