#pragma once

#include "types.h"

struct StorageElementComponent {
  StorageElementComponent(): elementId(0), type(0), data(L"") {}

  StorageElementComponent(Id elementId_, int type_, std::wstring data_)
      : elementId(elementId_), type(type_), data(std::move(data_)) {}

  bool operator<(const StorageElementComponent& other) const {
    if(elementId != other.elementId) {
      return elementId < other.elementId;
    } else if(type != other.type) {
      return type < other.type;
    } else {
      return data < other.data;
    }
  }

  Id elementId;
  int type;
  std::wstring data;
};