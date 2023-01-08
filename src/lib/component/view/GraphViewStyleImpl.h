#pragma once

#include "Node.h"

class GraphViewStyleImpl {
public:
  virtual ~GraphViewStyleImpl() {}
  virtual float getCharWidth(const std::string& fontName, size_t fontSize) = 0;
  virtual float getCharHeight(const std::string& fontName, size_t fontSize) = 0;
  virtual float getGraphViewZoomDifferenceForPlatform() = 0;
};