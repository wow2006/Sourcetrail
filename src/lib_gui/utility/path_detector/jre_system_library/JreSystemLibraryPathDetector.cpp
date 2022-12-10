#include "JreSystemLibraryPathDetector.h"

#include "ApplicationSettings.h"
#include "FilePath.hpp"
#include "FileSystem.h"
#include "JavaPathDetector.h"

JreSystemLibraryPathDetector::JreSystemLibraryPathDetector(std::shared_ptr<JavaPathDetector> javaPathDetector)
    : PathDetector(javaPathDetector->getName() + " System Library"), m_javaPathDetector(javaPathDetector) {}

std::vector<FilePath> JreSystemLibraryPathDetector::doGetPaths() const {
  std::vector<FilePath> paths;
  for (const FilePath& jrePath : m_javaPathDetector->getPaths()) {
    const FilePath javaRoot = jrePath.getParentDirectory().getParentDirectory().getParentDirectory();
    for (const FilePath& jarPath : FileSystem::getFilePathsFromDirectory(javaRoot.getConcatenated(L"lib"), {L".jar"})) {
      paths.push_back(jarPath);
    }
    if (!paths.empty()) {
      break;
    }
  }
  return paths;
}
