#ifndef FULLTEXTSEARCH_INDEX_H
#define FULLTEXTSEARCH_INDEX_H

#include <mutex>
#include <unordered_map>
#include <vector>

#include "SuffixArray.h"
#include "types.hpp"

class StorageAccess;

// contains all fulltextsearch results of one file
struct FullTextSearchResult {
  Id fileId;
  std::vector<int> positions;
};

struct FullTextSearchFile {
  FullTextSearchFile(Id fileId, SuffixArray array) : fileId(fileId), array(array){};
  Id fileId;
  SuffixArray array;
};

class FullTextSearchIndex {
 public:
  void addFile(Id fileId, const std::wstring& file);
  std::vector<FullTextSearchResult> searchForTerm(const std::wstring& term) const;

  size_t fileCount() const;

  void clear();

 private:
  mutable std::mutex m_filesMutex;
  std::vector<FullTextSearchFile> m_files;
};

#endif  // FULLTEXTSEARCH_INDEX_H
