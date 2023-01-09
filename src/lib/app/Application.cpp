#include "Application.h"

#include "ApplicationSettings.h"
#include "ColorScheme.h"
#include "DialogView.h"
#include "FileLogger.h"
#include "GraphViewStyle.h"
#include "IDECommunicationController.h"
#include "LogManager.h"
#include "MainView.h"
#include "MessageFilterErrorCountUpdate.h"
#include "MessageFilterFocusInOut.h"
#include "MessageFilterSearchAutocomplete.h"
#include "MessageQueue.h"
#include "MessageQuitApplication.h"
#include "MessageStatus.h"
#include "NetworkFactory.h"
#include "ProjectSettings.h"
#include "SharedMemoryGarbageCollector.h"
#include "StorageCache.h"
#include "TabId.h"
#include "TaskManager.h"
#include "TaskScheduler.h"
#include "UserPaths.h"
#include "Version.h"
#include "ViewFactory.h"
#include "logging.h"
#include "tracing.h"
#include "utilityString.h"
#include "utilityUuid.h"

#include "CppSQLite3.h"

namespace lib::app {

std::shared_ptr<Application> Application::s_instance; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

std::string Application::s_uuid; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

void Application::createInstance(const Version& version,
                                 ViewFactory* viewFactory,
                                 NetworkFactory* networkFactory) {
  bool hasGui = (viewFactory != nullptr);

  Version::setApplicationVersion(version);

  if(hasGui) {
    GraphViewStyle::setImpl(viewFactory->createGraphStyleImpl());
  }

  loadSettings();

  auto* collector = SharedMemoryGarbageCollector::createInstance();
  if(collector != nullptr) {
    collector->run(Application::getUUID());
  }

  TaskManager::createScheduler(TabId::app());
  TaskManager::createScheduler(TabId::background());
  MessageQueue::getInstance();

  s_instance = std::shared_ptr<Application>(new Application(hasGui));

  s_instance->m_storageCache = std::make_shared<StorageCache>();

  if(hasGui) {
    s_instance->m_mainView = viewFactory->createMainView(s_instance->m_storageCache.get());
    s_instance->m_mainView->setup();
  }

  if(networkFactory != nullptr) {
    s_instance->m_ideCommunicationController = networkFactory->createIDECommunicationController(
        s_instance->m_storageCache.get());
    s_instance->m_ideCommunicationController->startListening();
  }

  s_instance->startMessagingAndScheduling();
}

std::shared_ptr<Application> Application::getInstance() {
  return s_instance;
}

void Application::destroyInstance() {
  MessageQueue::getInstance()->stopMessageLoop();
  TaskManager::destroyScheduler(TabId::background());
  TaskManager::destroyScheduler(TabId::app());

  s_instance.reset();
}

std::string Application::getUUID() {
  if(s_uuid.empty()) {
    s_uuid = utility::getUuidString();
  }

  return s_uuid;
}

void Application::loadSettings() {
  MessageStatus(L"Load settings: " + UserPaths::getAppSettingsFilePath().wstr()).dispatch();

  auto settings = ApplicationSettings::getInstance();
  settings->load(UserPaths::getAppSettingsFilePath());

  LogManager::getInstance()->setLoggingEnabled(settings->getLoggingEnabled());
  auto* pLogger = LogManager::getInstance()->getLoggerByType("FileLogger");
  if(pLogger != nullptr) {
    auto *const fileLogger = dynamic_cast<FileLogger*>(pLogger);
    fileLogger->setLogDirectory(settings->getLogDirectoryPath());
    fileLogger->setFileName(FileLogger::generateDatedFileName(L"log"));
  }

  loadStyle(settings->getColorSchemePath());
}

void Application::loadStyle(const utility::file::FilePath& colorSchemePath) {
  ColorScheme::getInstance()->load(colorSchemePath);
  GraphViewStyle::loadStyleSettings();
}

Application::Application(bool withGUI): m_hasGUI(withGUI) {}

Application::~Application() {
  if(m_hasGUI) {
    m_mainView->saveLayout();
  }

  auto* pCollector = SharedMemoryGarbageCollector::getInstance();
  if(pCollector != nullptr) {
    pCollector->stop();
  }
}

int Application::handleDialog(const std::wstring& message) {
  return getDialogView(DialogView::UseCase::GENERAL)->confirm(message);
}

int Application::handleDialog(const std::wstring& message, const std::vector<std::wstring>& options) {
  return getDialogView(DialogView::UseCase::GENERAL)->confirm(message, options);
}

std::shared_ptr<DialogView> Application::getDialogView(DialogView::UseCase useCase) {
  if(m_mainView) {
    return m_mainView->getDialogView(useCase);
  }

  return std::make_shared<DialogView>(useCase, nullptr);
}

void Application::updateHistoryMenu(std::shared_ptr<MessageBase> message) {
  m_mainView->updateHistoryMenu(std::move(message));
}

void Application::updateBookmarks(const std::vector<std::shared_ptr<Bookmark>>& bookmarks) {
  m_mainView->updateBookmarksMenu(bookmarks);
}

void Application::handleMessage(MessageActivateWindow* /*message*/) {
  if(m_hasGUI) {
    m_mainView->activateWindow();
  }
}

void Application::handleMessage(MessageCloseProject* /*message*/) {
  if(m_project && m_project->isIndexing()) {
    MessageStatus(L"Cannot close the project while indexing.", true, false).dispatch();
    return;
  }

  m_project.reset();
  updateTitle();
  m_mainView->clear();
}

void Application::handleMessage(MessageIndexingFinished* /*message*/) {
  logStorageStats();

  if(m_hasGUI) {
    MessageRefreshUI().afterIndexing().dispatch();
  } else {
    MessageQuitApplication().dispatch();
  }
}

void Application::handleMessage(MessageLoadProject* message) {
  TRACE("app load project");

  utility::file::FilePath projectSettingsFilePath(message->projectSettingsFilePath);
  loadWindow(projectSettingsFilePath.empty());

  if(projectSettingsFilePath.empty()) {
    return;
  }

  if(m_project && m_project->isIndexing()) {
    MessageStatus(L"Cannot load another project while indexing.", true, false).dispatch();
    return;
  }

  if(m_project && projectSettingsFilePath == m_project->getProjectSettingsFilePath()) {
    if(message->settingsChanged && m_hasGUI) {
      m_project->setStateOutdated();
      refreshProject(REFRESH_ALL_FILES, message->shallowIndexingRequested);
    }
  } else {
    MessageStatus(L"Loading Project: " + projectSettingsFilePath.wstr(), false, true).dispatch();

    m_project.reset();

    if(m_hasGUI) {
      m_mainView->clear();
    }

    try {
      updateRecentProjects(projectSettingsFilePath);

      m_storageCache->clear();
      m_storageCache->setSubject(
          std::weak_ptr<StorageAccess>());    // TODO(Hussein): check if this is really required.

      m_project = std::make_shared<Project>(
          std::make_shared<ProjectSettings>(projectSettingsFilePath),
          m_storageCache.get(),
          getUUID(),
          hasGUI());

      if(m_project) {
        m_project->load(getDialogView(DialogView::UseCase::GENERAL));
      } else {
        LOG_ERROR_STREAM(<< "Failed to load project.");
        MessageStatus(L"Failed to load project: " + projectSettingsFilePath.wstr(), true).dispatch();
      }

      updateTitle();
    } catch(std::exception& e) {
      const std::wstring erroMessage = L"Failed to load project at \"" +
          projectSettingsFilePath.wstr() + L"\" with exception: " + utility::decodeFromUtf8(e.what());
      LOG_ERROR(erroMessage);
      MessageStatus(erroMessage, true).dispatch();
    } catch(CppSQLite3Exception& e) {
      const std::wstring erroMessage = L"Failed to load project at \"" +
          projectSettingsFilePath.wstr() + L"\" with sqlite exception: " +
          utility::decodeFromUtf8(e.errorMessage());
      LOG_ERROR(erroMessage);
      MessageStatus(erroMessage, true).dispatch();
    } catch(...) {
      const std::wstring erroMessage = L"Failed to load project at \"" +
          projectSettingsFilePath.wstr() + L"\" with unknown exception.";
      LOG_ERROR(erroMessage);
      MessageStatus(erroMessage, true).dispatch();
    }

    if(message->refreshMode != REFRESH_NONE) {
      refreshProject(message->refreshMode, message->shallowIndexingRequested);
    }
  }
}

void Application::handleMessage(MessageRefresh* message) {
  TRACE("app refresh");

  refreshProject(message->all ? REFRESH_ALL_FILES : REFRESH_UPDATED_FILES, false);
}

void Application::handleMessage(MessageRefreshUI* message) {
  TRACE("ui refresh");

  if(m_hasGUI) {
    updateTitle();

    if(message->loadStyle) {
      loadStyle(ApplicationSettings::getInstance()->getColorSchemePath());
    }

    m_mainView->refreshViews();

    m_mainView->refreshUIState(message->isAfterIndexing);
  }
}

void Application::handleMessage(MessageSwitchColorScheme* message) {
  MessageStatus(L"Switch color scheme: " + message->colorSchemePath.wstr()).dispatch();

  loadStyle(message->colorSchemePath);
  MessageRefreshUI().noStyleReload().dispatch();
}

void Application::startMessagingAndScheduling() {
  TaskManager::getScheduler(TabId::app())->startSchedulerLoopThreaded();
  TaskManager::getScheduler(TabId::background())->startSchedulerLoopThreaded();

  MessageQueue* queue = MessageQueue::getInstance().get();
  queue->addMessageFilter(std::make_shared<MessageFilterErrorCountUpdate>());
  queue->addMessageFilter(std::make_shared<MessageFilterFocusInOut>());
  queue->addMessageFilter(std::make_shared<MessageFilterSearchAutocomplete>());

  queue->setSendMessagesAsTasks(true);
  queue->startMessageLoopThreaded();
}

void Application::loadWindow(bool showStartWindow) {
  if(!m_hasGUI) {
    return;
  }

  if(!m_loadedWindow) {
    // TODO(Hussein): Check the use of the next line.
    [[maybe_unused]] auto* pAppSettings = ApplicationSettings::getInstance().get();

    updateTitle();

    m_mainView->loadWindow(showStartWindow);
    m_loadedWindow = true;
  } else if(!showStartWindow) {
    m_mainView->hideStartScreen();
  }
}

void Application::refreshProject(RefreshMode refreshMode, bool shallowIndexingRequested) {
  if(m_project && checkSharedMemory()) {
    m_project->refresh(
        getDialogView(DialogView::UseCase::INDEXING), refreshMode, shallowIndexingRequested);

    if(!m_hasGUI && !m_project->isIndexing()) {
      MessageQuitApplication().dispatch();
    }
  }
}

void Application::updateRecentProjects(const utility::file::FilePath& projectSettingsFilePath) {
  if(m_hasGUI) {
    ApplicationSettings* appSettings = ApplicationSettings::getInstance().get();
    std::vector<utility::file::FilePath> recentProjects = appSettings->getRecentProjects();
    if(!recentProjects.empty()) {
      auto itr = std::find(recentProjects.begin(), recentProjects.end(), projectSettingsFilePath);
      if(itr != recentProjects.end()) {
        recentProjects.erase(itr);
      }
    }

    recentProjects.insert(recentProjects.begin(), projectSettingsFilePath);
    while(recentProjects.size() > appSettings->getMaxRecentProjectsCount()) {
      recentProjects.pop_back();
    }

    appSettings->setRecentProjects(recentProjects);
    appSettings->save(UserPaths::getAppSettingsFilePath());

    m_mainView->updateRecentProjectMenu();
  }
}

void Application::logStorageStats() const {
  if(!ApplicationSettings::getInstance()->getLoggingEnabled()) {
    return;
  }

  std::stringstream stringStream;
  StorageStats stats = m_storageCache->getStorageStats();

  stringStream << "\nGraph:\n";
  stringStream << "\t" << stats.nodeCount << " Nodes\n";
  stringStream << "\t" << stats.edgeCount << " Edges\n";

  stringStream << "\nCode:\n";
  stringStream << "\t" << stats.fileCount << " Files\n";
  stringStream << "\t" << stats.fileLOCCount << " Lines of Code\n";


  ErrorCountInfo errorCount = m_storageCache->getErrorCount();

  stringStream << "\nErrors:\n";
  stringStream << "\t" << errorCount.total << " Errors\n";
  stringStream << "\t" << errorCount.fatal << " Fatal Errors\n";

  LOG_INFO(stringStream.str());
}

void Application::updateTitle() {
  if(m_hasGUI) {
    std::wstring title = L"Sourcetrail";

    if(m_project) {
      utility::file::FilePath projectPath = m_project->getProjectSettingsFilePath();

      if(!projectPath.empty()) {
        title += L" - " + projectPath.fileName();
      }
    }

    m_mainView->setTitle(title);
  }
}

bool Application::checkSharedMemory() {
  std::wstring error = utility::decodeFromUtf8(SharedMemory::checkSharedMemory(getUUID()));
  if(!error.empty()) {
    MessageStatus(
        L"Error on accessing shared memory. Indexing not possible. "
        "Please restart computer or run as admin: " +
            error,
        true)
        .dispatch();
    handleDialog(L"There was an error accessing shared memory on your computer: " + error +
                 L"\n\n"
                 "Project indexing is not possible. Please restart your computer or try running "
                 "Sourcetrail as admin.");
    return false;
  }

  return true;
}

}    // namespace lib::app
