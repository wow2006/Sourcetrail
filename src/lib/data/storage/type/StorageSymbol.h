#pragma once

#include "DefinitionKind.h"
#include "types.h"

struct StorageSymbol {
  StorageSymbol(): id(0), definitionKind(definitionKindToInt(DEFINITION_NONE)) {}

  StorageSymbol(Id id_, int definitionKind_): id(id_), definitionKind(definitionKind_) {}

  Id id;
  int definitionKind;
};