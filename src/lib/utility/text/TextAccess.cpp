#include "TextAccess.h"

#include <fstream>
#include <iostream>
#include <numeric>

#include "logging.h"

namespace {

std::istream& safeGetline(std::istream& inputStream, std::string& text) {
  text.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry sentry(inputStream, true);
  auto* pOldStream = inputStream.rdbuf();

  while (true) {
    const int chr = pOldStream->sbumpc();
    switch (chr) {
    case '\n':
      return inputStream;
    case '\r':
      if (pOldStream->sgetc() == '\n') {
        pOldStream->sbumpc();
      }
      return inputStream;
    case std::streambuf::traits_type::eof():
      // Also handle the case when the last line has no line ending
      if (text.empty()) {
        inputStream.setstate(std::ios::eofbit);
      }
      return inputStream;
    default:
      text += static_cast<char>(chr);
    }
  }
}

}    // namespace

std::shared_ptr<TextAccess> TextAccess::createFromFile(const utility::file::FilePath& filePath) {
  if(!filePath.exists()) {
    return nullptr;
  }

  std::shared_ptr<TextAccess> result(new TextAccess());

  result->m_filePath = filePath;
  result->m_lines = readFile(filePath);

  return result;
}

std::shared_ptr<TextAccess> TextAccess::createFromString(const std::string& text,
                                                         const utility::file::FilePath& filePath) {
  std::shared_ptr<TextAccess> result(new TextAccess());

  result->m_lines = splitStringByLines(text);
  result->m_filePath = filePath;

  return result;
}

std::shared_ptr<TextAccess> TextAccess::createFromLines(const std::vector<std::string>& lines,
                                                        const utility::file::FilePath& filePath) {
  std::shared_ptr<TextAccess> result(new TextAccess());

  result->m_lines = lines;
  result->m_filePath = filePath;

  return result;
}

TextAccess::TextAccess() = default;

TextAccess::TextAccess(TextAccess&&) noexcept = default;

TextAccess& TextAccess::operator=(TextAccess&&) noexcept = default;

TextAccess::~TextAccess() noexcept = default;

std::vector<std::string> TextAccess::getLines(uint32_t firstLineNumber,
                                              uint32_t lastLineNumber) {
  if (!checkIndexIntervalInRange(firstLineNumber, lastLineNumber)) {
    return {};
  }

  // -1 to correct for use as index
  auto first = m_lines.begin() + firstLineNumber - 1;
  auto last  = m_lines.begin() + lastLineNumber;

  return {first, last};
}

std::vector<std::string> TextAccess::readFile(const utility::file::FilePath& filePath) {
  std::vector<std::string> result;

  try {
    std::ifstream srcFile;
    srcFile.open(filePath.str(), std::ios::binary | std::ios::in);

    if (srcFile.fail()) {
      LOG_ERROR(L"Could not open file " + filePath.wstr());
      return result;
    }

    while (!srcFile.eof()) {
      std::string line;
      safeGetline(srcFile, line);
      result.push_back(line + '\n');
    }

    srcFile.close();
  } catch (std::exception& e) {
    LOG_ERROR_STREAM(<< "Exception thrown while reading file \"" << filePath.str()
                     << "\": " << e.what());
    result.clear();
  } catch (...) {
    LOG_ERROR_STREAM(<< "Unknown exception thrown while reading file \"" << filePath.str() << "\"");
    result.clear();
  }

  if (!result.empty()) {
    std::string last = result.back().substr(0, result.back().size() - 1);
    result.pop_back();
    if (!last.empty()) {
      result.push_back(last);
    }
  }

  return result;
}

std::vector<std::string> TextAccess::splitStringByLines(const std::string& text) {
  std::vector<std::string> result;
  size_t prevIndex = 0;
  size_t index = text.find('\n');

  while (index != std::string::npos) {
    result.push_back(text.substr(prevIndex, index - prevIndex) + '\n');

    prevIndex = index + 1;
    index = text.find('\n', prevIndex);
  }

  if (prevIndex < text.length()) {
    result.push_back(text.substr(prevIndex));
  }

  return result;
}

bool TextAccess::checkIndexInRange(uint32_t index) const {
  if (index < 1) {
    LOG_WARNING_STREAM(<< "Line numbers start with one, is " << index);
    return false;
  } else if (index > m_lines.size()) {
    LOG_WARNING_STREAM(<< "Tried to access index " << index << ". Maximum index is "
                       << m_lines.size());
    return false;
  }

  return true;
}

bool TextAccess::checkIndexIntervalInRange(uint32_t firstIndex,
                                           uint32_t lastIndex) const {
  if (!checkIndexInRange(firstIndex) || !checkIndexInRange(lastIndex)) {
    return false;
  }

  if (firstIndex > lastIndex) {
    LOG_WARNING_STREAM(<< "Index 'firstLine' has to be lower or equal index 'lastLine', is "
                       << firstIndex << " > " << lastIndex);
    return false;
  }

  return true;
}
