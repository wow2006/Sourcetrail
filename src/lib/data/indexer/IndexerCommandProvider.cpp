#include "IndexerCommandProvider.h"


IndexerCommandProvider::~IndexerCommandProvider() = default;

bool IndexerCommandProvider::empty() const {
  return size() == 0;
}
