#include "ConfigManager.h"

#include <algorithm>
#include <iterator>
#include <set>

#include "tinyxml.h"

#include "FilePath.h"
#include "TextAccess.h"
#include "logging.h"
#include "utility.h"
#include "utilityString.h"

std::shared_ptr<ConfigManager> ConfigManager::createEmpty() {
  return std::shared_ptr<ConfigManager>(new ConfigManager());
}

std::shared_ptr<ConfigManager> ConfigManager::createAndLoad(
    const std::shared_ptr<TextAccess>& textAccess) {
  std::shared_ptr<ConfigManager> configManager = std::shared_ptr<ConfigManager>(new ConfigManager());
  configManager->load(textAccess);
  return configManager;
}

std::shared_ptr<ConfigManager> ConfigManager::createCopy() {
  return std::shared_ptr<ConfigManager>(new ConfigManager(*this));
}

void ConfigManager::clear() {
  m_values.clear();
}

bool ConfigManager::getValue(const std::string& key, std::string& value) const {
  auto iterator = m_values.find(key);

  if(iterator != m_values.end()) {
    value = iterator->second;
    return true;
  }
  if(m_warnOnEmptyKey) {
    // LOG_WARNING("value " + key + " is not present in config.");
  }
  return false;
}

bool ConfigManager::getValue(const std::string& key, std::wstring& value) const {
  std::string valueString;
  if(getValue(key, valueString)) {
    value = utility::decodeFromUtf8(valueString);
    return true;
  }
  return false;
}

bool ConfigManager::getValue(const std::string& key, int& value) const {
  std::string valueString;
  if(getValue(key, valueString)) {
    value = atoi(valueString.c_str());
    return true;
  }
  return false;
}

bool ConfigManager::getValue(const std::string& key, float& value) const {
  std::string valueString;
  if(getValue(key, valueString)) {
    std::stringstream stringstream;
    stringstream << valueString;
    stringstream >> value;
    return true;
  }
  return false;
}

bool ConfigManager::getValue(const std::string& key, bool& value) const {
  std::string valueString;
  if(getValue(key, valueString)) {
    value = (atoi(valueString.c_str()) != 0);
    return true;
  }
  return false;
}

bool ConfigManager::getValue(const std::string& key, FilePath& value) const {
  std::wstring valueString;
  if(getValue(key, valueString)) {
    value = FilePath(valueString);
    return true;
  }
  return false;
}

bool ConfigManager::getValues(const std::string& key, std::vector<std::string>& values) const {
  std::pair<std::multimap<std::string, std::string>::const_iterator,
            std::multimap<std::string, std::string>::const_iterator>
      ret;
  ret = m_values.equal_range(key);

  if(ret.first != ret.second) {
    for(auto iterator = ret.first; iterator != ret.second; ++iterator) {
      values.push_back(iterator->second);
    }
    return true;
  }
  if(m_warnOnEmptyKey) {
    // LOG_WARNING("value " + key + " is not present in config.");
  }
  return false;
}

bool ConfigManager::getValues(const std::string& key, std::vector<std::wstring>& values) const {
  std::vector<std::string> valuesStringVector;
  if(getValues(key, valuesStringVector)) {
    for(const std::string& valueString: valuesStringVector) {
      values.push_back(utility::decodeFromUtf8(valueString));
    }
    return true;
  }
  return false;
}


bool ConfigManager::getValues(const std::string& key, std::vector<int>& values) const {
  std::vector<std::string> valuesStringVector;
  if(getValues(key, valuesStringVector)) {
    for(const std::string& valueString: valuesStringVector) {
      values.push_back(atoi(valueString.c_str()));
    }
    return true;
  }
  return false;
}

bool ConfigManager::getValues(const std::string& key, std::vector<float>& values) const {
  std::vector<std::string> valuesStringVector;
  if(getValues(key, valuesStringVector)) {
    for(const std::string& valueString: valuesStringVector) {
      values.push_back(static_cast<float>(atof(valueString.c_str())));
    }
    return true;
  }
  return false;
}

bool ConfigManager::getValues(const std::string& key, std::vector<bool>& values) const {
  std::vector<std::string> valuesStringVector;
  if(getValues(key, valuesStringVector)) {
    for(const std::string& valueString: valuesStringVector) {
      values.push_back(atoi(valueString.c_str()) != 0);
    }
    return true;
  }
  return false;
}

bool ConfigManager::getValues(const std::string& key, std::vector<FilePath>& values) const {
  std::vector<std::wstring> valuesStringVector;
  if(getValues(key, valuesStringVector)) {
    for(const std::wstring& valueString: valuesStringVector) {
      values.emplace_back(FilePath(valueString));
    }
    return true;
  }
  return false;
}

void ConfigManager::setValue(const std::string& key, const std::string& value) {
  auto iterator = m_values.find(key);

  if(iterator != m_values.end()) {
    iterator->second = value;
  } else {
    m_values.emplace(key, value);
  }
}

void ConfigManager::setValue(const std::string& key, const std::wstring& value) {
  setValue(key, utility::encodeToUtf8(value));
}

void ConfigManager::setValue(const std::string& key, int value) {
  setValue(key, std::to_string(value));
}

void ConfigManager::setValue(const std::string& key, float value) {
  std::stringstream stringstream;
  stringstream << value;
  setValue(key, stringstream.str());
}

void ConfigManager::setValue(const std::string& key, bool value) {
  setValue(key, std::string(value ? "1" : "0"));
}

void ConfigManager::setValue(const std::string& key, const FilePath& value) {
  setValue(key, value.wstr());
}

void ConfigManager::setValues(const std::string& key, const std::vector<std::string>& values) {
  auto iterator = m_values.find(key);

  if(iterator != m_values.end()) {
    m_values.erase(key);
  }
  for(auto value: values) {
    m_values.emplace(key, value);
  }
}

void ConfigManager::setValues(const std::string& key, const std::vector<std::wstring>& values) {
  std::vector<std::string> stringValues;
  std::ranges::transform(values, std::back_inserter(stringValues), [](const auto& value) {
    return utility::encodeToUtf8(value);
  });
  setValues(key, stringValues);
}

void ConfigManager::setValues(const std::string& key, const std::vector<int>& values) {
  std::vector<std::string> stringValues;
  std::ranges::transform(values, std::back_inserter(stringValues), [](const auto& value) {
    return std::to_string(value);
  });
  setValues(key, stringValues);
}

void ConfigManager::setValues(const std::string& key, const std::vector<float>& values) {
  std::vector<std::string> stringValues;
  std::ranges::transform(values, std::back_inserter(stringValues), [](const auto& value) {
    return std::to_string(value);
  });
  setValues(key, stringValues);
}

void ConfigManager::setValues(const std::string& key, const std::vector<bool>& values) {
  std::vector<std::string> stringValues;
  std::ranges::transform(values, std::back_inserter(stringValues), [](const auto& value) {
    return std::string(value ? "1" : "0");
  });
  setValues(key, stringValues);
}

void ConfigManager::setValues(const std::string& key, const std::vector<FilePath>& values) {
  std::vector<std::wstring> stringValues;
  std::ranges::transform(
      values, std::back_inserter(stringValues), [](const auto& value) { return value.wstr(); });
  setValues(key, stringValues);
}

// NOLINTNEXTLINE(misc-no-recursion)
void ConfigManager::removeValues(const std::string& key) {
  for(const auto& sublevelKey: getSublevelKeys(key)) {
    removeValues(sublevelKey);
  }
  m_values.erase(key);
}

bool ConfigManager::isValueDefined(const std::string& key) const {
  auto iterator = m_values.find(key);

  return iterator != m_values.end();
}

std::vector<std::string> ConfigManager::getSublevelKeys(const std::string& key) const {
  std::set<std::string> keys;
  for(const auto& [hKey, value]: m_values) {
    if(utility::isPrefix(key, hKey)) {
      size_t startPos = hKey.find('/', key.size());
      if(startPos == key.size()) {
        std::string sublevelKey = hKey.substr(0, hKey.find('/', startPos + 1));
        keys.insert(sublevelKey);
      }
    }
  }
  return utility::toVector(keys);
}

bool ConfigManager::load(const std::shared_ptr<TextAccess>& textAccess) {
  TiXmlDocument doc;
  const char* pTest = doc.Parse(textAccess->getText().c_str(), nullptr, TIXML_ENCODING_UTF8);
  if(pTest != nullptr) {
    TiXmlHandle docHandle(&doc);
    TiXmlNode* rootNode = docHandle.FirstChild("config").ToNode();
    if(rootNode == nullptr) {
      LOG_ERROR("No rootelement 'config' in the configfile");
      return false;
    }
    for(auto* childNode = rootNode->FirstChild(); childNode != nullptr;
        childNode = childNode->NextSibling()) {
      parseSubtree(childNode, "");
    }
  } else {
    LOG_ERROR("Unable to load file.");
    return false;
  }
  return true;
}

bool ConfigManager::save(const std::string& filepath) {
  std::string output;
  return createXmlDocument(true, filepath, output);
}

void ConfigManager::setWarnOnEmptyKey(bool warnOnEmptyKey) const {
  m_warnOnEmptyKey = warnOnEmptyKey;
}

ConfigManager::ConfigManager() = default;

ConfigManager::~ConfigManager() = default;

ConfigManager::ConfigManager(const ConfigManager& other) = default;

ConfigManager::ConfigManager(ConfigManager&&) noexcept = default;

bool ConfigManager::createXmlDocument(bool saveAsFile,
                                      const std::string& filepath,
                                      std::string& output) {
  bool success = true;
  TiXmlDocument doc;
  auto* decl = new TiXmlDeclaration("1.0", "utf-8", "");    // NOLINT(cppcoreguidelines-owning-memory)
  doc.LinkEndChild(decl);
  auto* root = new TiXmlElement("config");    // NOLINT(cppcoreguidelines-owning-memory)
  doc.LinkEndChild(root);

  for(const auto& [key, value]: m_values) {
    if(key.empty() || value.empty()) {
      continue;
    }

    auto tokens = utility::splitToVector(key, "/");

    TiXmlElement* element = doc.RootElement();
    TiXmlElement* child = nullptr;
    while(tokens.size() > 1) {
      child = element->FirstChildElement(tokens.front().c_str());
      if(child == nullptr) {
        child = new TiXmlElement(tokens.front().c_str());    // NOLINT(cppcoreguidelines-owning-memory)
        element->LinkEndChild(child);
      }
      tokens.erase(tokens.begin());
      element = child;
    }

    child = new TiXmlElement(tokens.front().c_str());    // NOLINT(cppcoreguidelines-owning-memory)
    element->LinkEndChild(child);
    auto* text = new TiXmlText(value.c_str());    // NOLINT(cppcoreguidelines-owning-memory)
    child->LinkEndChild(text);
  }

  if(saveAsFile) {
    success = doc.SaveFile(filepath.c_str());
  } else {
    TiXmlPrinter printer;
    doc.Accept(&printer);
    output = printer.CStr();
  }
  success = doc.SaveFile(filepath.c_str());
  doc.Clear();
  return success;
}

// NOLINTNEXTLINE(misc-no-recursion)
void ConfigManager::parseSubtree(TiXmlNode* currentNode, const std::string& currentPath) {
  if(currentNode->Type() == TiXmlNode::TINYXML_TEXT) {
    std::string key = currentPath.substr(0, currentPath.size() - 1);
    m_values.insert(std::pair<std::string, std::string>(key, currentNode->ToText()->Value()));
  } else {
    for(auto* childNode = currentNode->FirstChild(); childNode != nullptr;
        childNode = childNode->NextSibling()) {
      parseSubtree(childNode, currentPath + std::string(currentNode->Value()) + "/");
    }
  }
}

std::string ConfigManager::toString() {
  std::string output;
  createXmlDocument(false, "", output);
  return output;
}
