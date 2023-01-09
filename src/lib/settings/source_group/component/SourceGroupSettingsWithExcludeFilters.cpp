#include "SourceGroupSettingsWithExcludeFilters.h"

#include "FilePathFilter.h"
#include "FileSystem.h"
#include "ProjectSettings.h"
#include "utility.h"
#include "utilityFile.h"

SourceGroupSettingsWithExcludeFilters::~SourceGroupSettingsWithExcludeFilters() = default;

std::vector<std::wstring> SourceGroupSettingsWithExcludeFilters::getExcludeFilterStrings() const {
  return m_excludeFilters;
}

std::vector<utility::file::FilePathFilter> SourceGroupSettingsWithExcludeFilters::
    getExcludeFiltersExpandedAndAbsolute() const {
  return getFiltersExpandedAndAbsolute(getExcludeFilterStrings());
}

void SourceGroupSettingsWithExcludeFilters::setExcludeFilterStrings(
    const std::vector<std::wstring>& excludeFilters) {
  m_excludeFilters = excludeFilters;
}

bool SourceGroupSettingsWithExcludeFilters::equals(const SourceGroupSettingsBase* other) const {
  const SourceGroupSettingsWithExcludeFilters* otherPtr =
      dynamic_cast<const SourceGroupSettingsWithExcludeFilters*>(other);

  return (otherPtr && utility::isPermutation(m_excludeFilters, otherPtr->m_excludeFilters));
}

void SourceGroupSettingsWithExcludeFilters::load(const utility::ConfigManager* config,
                                                 const std::string& key) {
  setExcludeFilterStrings(config->getValuesOrDefaults(
      key + "/exclude_filters/exclude_filter", std::vector<std::wstring>()));
}

void SourceGroupSettingsWithExcludeFilters::save(utility::ConfigManager* config,
                                                 const std::string& key) {
  config->setValues(key + "/exclude_filters/exclude_filter", getExcludeFilterStrings());
}

std::vector<utility::file::FilePathFilter> SourceGroupSettingsWithExcludeFilters::getFiltersExpandedAndAbsolute(
    const std::vector<std::wstring>& filterStrings) const {
  const utility::file::FilePath projectDirectoryPath = getProjectSettings()->getProjectDirectoryPath();

  std::vector<utility::file::FilePathFilter> result;

  for(const std::wstring& filterString: filterStrings) {
    if(!filterString.empty()) {
      const size_t wildcardPos = filterString.find(L"*");
      if(wildcardPos != filterString.npos) {
        std::wsmatch match;
        if(std::regex_search(filterString, match, std::wregex(L"[\\\\/]")) && !match.empty() &&
           match.position(0) < int(wildcardPos)) {
          auto p = utility::file::getExpandedAndAbsolutePath(
              utility::file::FilePath(match.prefix().str()), projectDirectoryPath);
          auto symLinkPaths = utility::file::FileSystem::getSymLinkedDirectories(p);
          symLinkPaths.insert(p);

          utility::append(
              result,
              utility::convert<utility::file::FilePath, utility::file::FilePathFilter>(
                  utility::toVector(symLinkPaths), [match](const auto& filePath) {
                    return utility::file::FilePathFilter(filePath.wstr() + L"/" +
                                                         match.suffix().str());
                  }));
        } else {
          result.push_back(utility::file::FilePathFilter(filterString));
        }
      } else {
        auto p = utility::file::getExpandedAndAbsolutePath(
            utility::file::FilePath(filterString), projectDirectoryPath);
        const bool isFile = p.exists() && !p.isDirectory();

        std::set<utility::file::FilePath> symLinkPaths =
            utility::file::FileSystem::getSymLinkedDirectories(p);
        symLinkPaths.insert(p);

        utility::append(
            result,
            utility::convert<utility::file::FilePath, utility::file::FilePathFilter>(
                utility::toVector(symLinkPaths), [isFile](const auto& filePath) {
                  return utility::file::FilePathFilter(filePath.wstr() + (isFile ? L"" : L"**"));
                }));
      }
    }
  }

  return result;
}
