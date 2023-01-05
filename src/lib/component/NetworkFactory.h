#pragma once

class IDECommunicationController;
class StorageAccess;
class UpdateChecker;

class NetworkFactory {
public:
  NetworkFactory();

  virtual ~NetworkFactory();

  virtual std::shared_ptr<IDECommunicationController> createIDECommunicationController(
      StorageAccess* storageAccess) const = 0;
};