#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCxxCdbPath : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithCxxCdbPath() = default;

  utility::file::FilePath getCompilationDatabasePath() const;
  utility::file::FilePath getCompilationDatabasePathExpandedAndAbsolute() const;
  void setCompilationDatabasePath(const utility::file::FilePath& compilationDatabasePath);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  utility::file::FilePath m_compilationDatabasePath;
};
