#pragma once
// Internal
#include "FilePath.h"

static utility::file::FilePath operator""_f(const char* pFilePath, std::size_t size) {
  return utility::file::FilePath {std::string {pFilePath, size}};
}

static utility::file::FilePath createFileWithSize(const std::filesystem::path& filePath, size_t fileSize) {
  const std::vector<uint8_t> buffer(fileSize);
  std::ofstream output(filePath, std::ios::binary);
  output.write(
      reinterpret_cast<const char*>(buffer.data()),    // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      static_cast<std::streamsize>(fileSize));
  return utility::file::FilePath {filePath};
}