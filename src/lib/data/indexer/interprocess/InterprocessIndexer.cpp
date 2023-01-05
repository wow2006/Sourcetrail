#include "InterprocessIndexer.h"

#include "IndexerCommand.h"
#include "IndexerComposite.h"
#include "LanguagePackageManager.h"
#include "ScopedFunctor.h"
#include "logging.h"

InterprocessIndexer::InterprocessIndexer(const std::string& uuid, Id processId)
    : m_interprocessIndexerCommandManager(uuid, processId, false)
    , m_interprocessIndexingStatusManager(uuid, processId, false)
    , m_interprocessIntermediateStorageManager(uuid, processId, false)
    , m_uuid(uuid)
    , m_processId(processId) {}

void InterprocessIndexer::work() {
  bool updaterThreadRunning = true;
  std::shared_ptr<std::thread> pUpdaterThread;
  std::shared_ptr<IndexerBase> pIndexer;

  try {
    LOG_INFO_STREAM(<< fmt::format("{} {}", m_processId, " starting up indexer"));
    pIndexer = LanguagePackageManager::getInstance()->instantiateSupportedIndexers();

    pUpdaterThread = std::make_shared<std::thread>([&]() {
      while(updaterThreadRunning) {
		constexpr auto TimeToWaitInMilliseconds = 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(TimeToWaitInMilliseconds));

        if(m_interprocessIndexingStatusManager.getIndexingInterrupted()) {
          LOG_INFO_STREAM(<< fmt::format("{} received indexer interrupt command.", m_processId));
          if(pIndexer) {
            pIndexer->interrupt();
          }
          updaterThreadRunning = false;
        }
      }
    });

    ScopedFunctor threadStopper([&]() {
      updaterThreadRunning = false;
      if(pUpdaterThread) {
        pUpdaterThread->join();
        pUpdaterThread.reset();
      }
    });

    while(auto indexerCommand = m_interprocessIndexerCommandManager.popIndexerCommand()) {
      LOG_INFO_STREAM(<< fmt::format("{} fetched indexer command for \"{}\"", m_processId, indexerCommand->getSourceFilePath().str()));
      LOG_INFO_STREAM(<< fmt::format("{} indexer commands left: {}", m_processId, m_interprocessIndexerCommandManager.indexerCommandCount()));

      while(updaterThreadRunning) {
        const size_t storageCount =
            m_interprocessIntermediateStorageManager.getIntermediateStorageCount();
        if(storageCount < 2) {
          break;
        }

        LOG_INFO_STREAM(<< fmt::format("{} waits, too many intermediate storages: {}", m_processId, storageCount));

		constexpr auto TimeToSleepInMilliseconds = 200;
        std::this_thread::sleep_for(std::chrono::milliseconds(TimeToSleepInMilliseconds));
      }

      if(!updaterThreadRunning) {
        break;
      }

      LOG_INFO_STREAM(<< fmt::format("{} updating indexer status with currently indexed filepath", m_processId));
      m_interprocessIndexingStatusManager.startIndexingSourceFile(indexerCommand->getSourceFilePath());

      LOG_INFO_STREAM(<< fmt::format("{} starting to index current file", m_processId));
      std::shared_ptr<IntermediateStorage> result = pIndexer->index(indexerCommand);

      if(result) {
        LOG_INFO_STREAM(<< fmt::format("{} pushing index to shared memory", m_processId));
        m_interprocessIntermediateStorageManager.pushIntermediateStorage(result);
      }

      LOG_INFO_STREAM(<< fmt::format("{} finalizing indexer status for current file", m_processId));
      m_interprocessIndexingStatusManager.finishIndexingSourceFile();

      LOG_INFO_STREAM(<< fmt::format("{} all done", m_processId));
    }
  } catch(boost::interprocess::interprocess_exception& exception) {
    LOG_ERROR_STREAM(<< fmt::format("{} error: {}", m_processId, exception.what()));
    throw exception;
  } catch(std::exception& exception) {
    LOG_ERROR_STREAM(<< fmt::format("{} error: {}", m_processId, exception.what()));
    throw exception;
  } catch(...) {
    LOG_ERROR_STREAM(<< fmt::format("{} something went wrong while running the indexer", m_processId));
  }

  LOG_INFO_STREAM(<< fmt::format("{} shutting down indexer", m_processId));
}
