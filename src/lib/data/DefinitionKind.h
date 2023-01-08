#pragma once

enum DefinitionKind {
	// these values need to be the same as DefinitionKind in Java code
	DEFINITION_NONE = 0,
	DEFINITION_IMPLICIT = 1,
	DEFINITION_EXPLICIT = 2
};

int definitionKindToInt(DefinitionKind definitionKind);

DefinitionKind intToDefinitionKind(int definitionKind);