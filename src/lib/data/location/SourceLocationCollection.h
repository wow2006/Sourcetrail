#pragma once

#include "LocationType.h"
#include "types.h"

namespace utility::file {
class FilePath;
} // namespace class utility::file
class SourceLocation;
class SourceLocationFile;

class SourceLocationCollection {
public:
  SourceLocationCollection();
  virtual ~SourceLocationCollection();

  const std::map<utility::file::FilePath, std::shared_ptr<SourceLocationFile>>& getSourceLocationFiles() const;

  size_t getSourceLocationCount() const;
  size_t getSourceLocationFileCount() const;

  std::shared_ptr<SourceLocationFile> getSourceLocationFileByPath(const utility::file::FilePath& filePath) const;
  SourceLocation* getSourceLocationById(Id locationId) const;

  SourceLocation* addSourceLocation(LocationType type,
                                    Id locationId,
                                    std::vector<Id> tokenIds,
                                    const utility::file::FilePath& filePath,
                                    size_t startLineNumber,
                                    size_t startColumnNumber,
                                    size_t endLineNumber,
                                    size_t endColumnNumber);

  SourceLocation* addSourceLocationCopy(const SourceLocation* location);
  void addSourceLocationCopies(const SourceLocationCollection* other);
  void addSourceLocationCopies(const SourceLocationFile* otherFile);

  void addSourceLocationFile(std::shared_ptr<SourceLocationFile> file);

  void forEachSourceLocationFile(std::function<void(std::shared_ptr<SourceLocationFile>)> func) const;
  void forEachSourceLocation(std::function<void(SourceLocation*)> func) const;

private:
  SourceLocationFile* createSourceLocationFile(const utility::file::FilePath& filePath,
                                               const std::wstring& language = L"",
                                               bool isWhole = false,
                                               bool isComplete = false,
                                               bool isIndexed = false);

  std::map<utility::file::FilePath, std::shared_ptr<SourceLocationFile>> m_files;
};

std::wostream& operator<<(std::wostream& ostream, const SourceLocationCollection& base);
