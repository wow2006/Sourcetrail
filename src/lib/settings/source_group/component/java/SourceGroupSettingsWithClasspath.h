#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
#include "SourceGroupSettingsComponent.h"

class SourceGroupSettingsWithClasspath : public SourceGroupSettingsComponent {
public:
  virtual ~SourceGroupSettingsWithClasspath() = default;

  std::vector<utility::file::FilePath> getClasspath() const;
  std::vector<utility::file::FilePath> getClasspathExpandedAndAbsolute() const;
  void setClasspath(const std::vector<utility::file::FilePath>& classpath);

  bool getUseJreSystemLibrary() const;
  void setUseJreSystemLibrary(bool useJreSystemLibrary);

protected:
  bool equals(const SourceGroupSettingsBase* other) const override;

  void load(const utility::ConfigManager* config, const std::string& key) override;
  void save(utility::ConfigManager* config, const std::string& key) override;

private:
  std::vector<utility::file::FilePath> m_classpath;
  bool m_useJreSystemLibrary = true;
};
