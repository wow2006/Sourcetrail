#include "Settings.h"

#include "FilePath.h"
#include "TextAccess.h"
#include "logging.h"

Settings::Settings() {
  clear();
}

Settings::Settings(const Settings& other)
    : m_config(other.m_config->createCopy()), m_filePath(other.m_filePath) {}

Settings& Settings::operator=(const Settings& other) {
  if(&other != this) {
    m_filePath = other.m_filePath;
    m_config = other.m_config->createCopy();
  }

  return *this;
}

Settings::Settings(Settings&& other) noexcept = default;

Settings& Settings::operator=(Settings&& other) noexcept = default;

Settings::~Settings() = default;

bool Settings::load(const FilePath& filePath, bool readOnly) {
  m_readOnly = readOnly;

  if(filePath.exists()) {
    m_config = ConfigManager::createAndLoad(TextAccess::createFromFile(filePath));
    m_filePath = filePath;
    return true;
  }
  clear();
  m_filePath = filePath;
  LOG_WARNING(L"File for Settings not found: " + filePath.wstr());
  return false;
}

bool Settings::loadFromString(const std::string& text, bool readOnly) {
  m_readOnly = readOnly;

  m_config = ConfigManager::createAndLoad(TextAccess::createFromString(text));
  m_filePath = FilePath();
  return true;
}

bool Settings::save() {
  if(m_readOnly) {
    return false;
  }

  bool success = false;
  if(m_config && !m_filePath.empty()) {
    success = m_config->save(m_filePath.str());
  }

  if(!success) {
    LOG_WARNING(L"Settings were not saved: " + m_filePath.wstr());
  }

  return success;
}

bool Settings::save(const FilePath& filePath) {
  setFilePath(filePath);

  return save();
}

void Settings::clear() {
  m_config = ConfigManager::createEmpty();
  m_filePath = FilePath();
}

const FilePath& Settings::getFilePath() const {
  return m_filePath;
}

size_t Settings::getVersion() const {
  return static_cast<size_t>(getValue<int>("version", 0));
}

void Settings::setVersion(size_t version) {
  setValue<int>("version", static_cast<int>(version));
}

void Settings::setFilePath(const FilePath& filePath) {
  m_filePath = filePath;
}

std::vector<FilePath> Settings::getPathValues(const std::string& key) const {
  std::vector<FilePath> paths;
  std::ranges::transform(getValues<std::wstring>(key, {}),
                         std::back_inserter(paths),
                         [](const auto& path) -> FilePath { return FilePath {path}; });
  return paths;
}

bool Settings::setPathValues(const std::string& key, const std::vector<FilePath>& paths) {
  std::vector<std::wstring> values;
  std::ranges::transform(
      paths, std::back_inserter(values), [](const auto& path) { return path.wstr(); });
  return setValues(key, values);
}

bool Settings::isValueDefined(const std::string& key) const {
  return m_config->isValueDefined(key);
}

void Settings::removeValues(const std::string& key) {
  m_config->removeValues(key);
}

void Settings::enableWarnings() const {
  m_config->setWarnOnEmptyKey(true);
}

void Settings::disableWarnings() const {
  m_config->setWarnOnEmptyKey(false);
}
