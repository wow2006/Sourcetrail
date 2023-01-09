#pragma once

namespace utility::file {
class FilePath;
} // namespace class utility::file
class IndexerCommand;

class IndexerCommandProvider {
public:
  virtual ~IndexerCommandProvider();
  virtual std::vector<utility::file::FilePath> getAllSourceFilePaths() const = 0;
  virtual std::shared_ptr<IndexerCommand> consumeCommand() = 0;
  virtual std::shared_ptr<IndexerCommand> consumeCommandForSourceFilePath(const utility::file::FilePath& filePath) = 0;
  virtual std::vector<std::shared_ptr<IndexerCommand>> consumeAllCommands() = 0;
  virtual void clear() = 0;
  virtual size_t size() const = 0;
  bool empty() const;
};