#pragma once

#include <memory>
#include <string>
#include <vector>

class FilePath;
enum class RefreshMode;

namespace commandline {

class CommandLineParserImpl;

class CommandLineParser {
public:
  /**
   * @brief Default consturctor
   *
   * @param version application version
   */
  explicit CommandLineParser(std::string version);

  /**
   * @brief Default deconstructor
   */
  ~CommandLineParser();

  CommandLineParser(const CommandLineParser&) = delete;
  CommandLineParser& operator=(const CommandLineParser&) = delete;
  CommandLineParser(CommandLineParser&&) = delete;
  CommandLineParser& operator=(CommandLineParser&&) = delete;

  /**
   * @brief Parse program input
   *
   * @param argc count of argments. first one should program name
   * @param argv array of strings of the argments
   */
  void preparse(int argc, char** argv);

  /**
   * @brief Parse program input
   *
   * @param args array of strings of the argments
   */
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
  std::unique_ptr<CommandLineParserImpl> m_pImpl;

};

}  // namespace commandline
