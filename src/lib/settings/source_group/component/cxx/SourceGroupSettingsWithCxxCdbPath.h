#pragma once

#include "FilePath.h"
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithCxxCdbPath : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithCxxCdbPath() = default;

  FilePath getCompilationDatabasePath() const;
  FilePath getCompilationDatabasePathExpandedAndAbsolute() const;
  void setCompilationDatabasePath(const FilePath& compilationDatabasePath);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  FilePath m_compilationDatabasePath;
};
