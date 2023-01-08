#pragma once

#include "FilePath.h"
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithClasspath : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithClasspath() = default;

  std::vector<FilePath> getClasspath() const;
  std::vector<FilePath> getClasspathExpandedAndAbsolute() const;
  void setClasspath(const std::vector<FilePath>& classpath);

  bool getUseJreSystemLibrary() const;
  void setUseJreSystemLibrary(bool useJreSystemLibrary);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  std::vector<FilePath> m_classpath;
  bool m_useJreSystemLibrary = true;
};
