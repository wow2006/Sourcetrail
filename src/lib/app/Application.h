#pragma once

#include "DialogView.h"
#include "MessageActivateWindow.h"
#include "MessageCloseProject.h"
#include "MessageIndexingFinished.h"
#include "MessageListener.h"
#include "MessageLoadProject.h"
#include "MessageRefresh.h"
#include "MessageRefreshUI.h"
#include "MessageSwitchColorScheme.h"
#include "Project.h"

class Bookmark;
class IDECommunicationController;
class MainView;
class NetworkFactory;
class StorageCache;
class UpdateChecker;
class Version;
class ViewFactory;

namespace lib::app {

/**
 * @brief The application instance
 */
class Application
    : public MessageListener<MessageActivateWindow>
    , public MessageListener<MessageCloseProject>
    , public MessageListener<MessageIndexingFinished>
    , public MessageListener<MessageLoadProject>
    , public MessageListener<MessageRefresh>
    , public MessageListener<MessageRefreshUI>
    , public MessageListener<MessageSwitchColorScheme> {
public:
  /**
   * @brief Create Application instance
   *
   * @param version Application version
   * @param viewFactory view factory
   * @param networkFactory network factory
   */
  static void createInstance(const Version& version,
                             ViewFactory* viewFactory,
                             NetworkFactory* networkFactory);

  /**
   * @name Disabled special member functions
   * @{ */
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;
  /**  @} */

  /**
   * @brief Sinigletone instance
   *
   * @return Shared pointer for the application
   */
  static std::shared_ptr<Application> getInstance();

  /**
   * @brief Destory the application instance
   */
  static void destroyInstance();

  static std::string getUUID();

  static void loadSettings();

  static void loadStyle(const FilePath& colorSchemePath);

  ~Application() override;

  [[nodiscard]] std::shared_ptr<Project> getCurrentProject() const {
    return m_project;
  }

  [[nodiscard]] FilePath getCurrentProjectPath() const {
    if(m_project) {
      return m_project->getProjectSettingsFilePath();
    }

    return {};
  }

  [[nodiscard]] bool isProjectLoaded() const {
    return m_project ? m_project->isLoaded() : false;
  }

  [[nodiscard]] bool hasGUI() const {
    return m_hasGUI;
  }

  int handleDialog(const std::wstring& message);

  int handleDialog(const std::wstring& message, const std::vector<std::wstring>& options);

  std::shared_ptr<DialogView> getDialogView(DialogView::UseCase useCase);

  void updateHistoryMenu(std::shared_ptr<MessageBase> message);

  void updateBookmarks(const std::vector<std::shared_ptr<Bookmark>>& bookmarks);

private:
  static std::shared_ptr<Application> s_instance; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

  static std::string s_uuid; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

  explicit Application(bool withGUI = true);

  /**
   * @name Message listener group
   * @{ */
  void handleMessage(MessageActivateWindow* message) override;

  void handleMessage(MessageCloseProject* message) override;

  void handleMessage(MessageIndexingFinished* message) override;

  void handleMessage(MessageLoadProject* message) override;

  void handleMessage(MessageRefresh* message) override;

  void handleMessage(MessageRefreshUI* message) override;

  void handleMessage(MessageSwitchColorScheme* message) override;
  /**  @} */

  void startMessagingAndScheduling();

  void loadWindow(bool showStartWindow);

  void refreshProject(RefreshMode refreshMode, bool shallowIndexingRequested);

  void updateRecentProjects(const FilePath& projectSettingsFilePath);

  void logStorageStats() const;

  void updateTitle();

  bool checkSharedMemory();

  const bool m_hasGUI;
  bool m_loadedWindow = false;

  std::shared_ptr<Project> m_project;
  std::shared_ptr<StorageCache> m_storageCache;

  std::shared_ptr<MainView> m_mainView;

  std::shared_ptr<IDECommunicationController> m_ideCommunicationController;
};

}    // namespace lib::app
