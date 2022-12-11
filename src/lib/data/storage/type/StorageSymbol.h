#ifndef STORAGE_SYMBOL_H
#define STORAGE_SYMBOL_H

#include "DefinitionKind.h"
#include "types.hpp"

struct StorageSymbol {
  StorageSymbol() : id(0), definitionKind(definitionKindToInt(DEFINITION_NONE)) {}

  StorageSymbol(Id id, int definitionKind) : id(id), definitionKind(definitionKind) {}

  Id id;
  int definitionKind;
};

#endif  // STORAGE_SYMBOL_H
