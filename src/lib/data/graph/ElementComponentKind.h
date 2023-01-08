#pragma once

enum class ElementComponentKind { NONE = 0, IS_AMBIGUOUS = 1 };

int elementComponentKindToInt(ElementComponentKind type);
ElementComponentKind intToElementComponentKind(int value);