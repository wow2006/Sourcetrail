#pragma once

// these values need to be the same as ReferenceKind in Java code
enum ReferenceKind {
  REFERENCE_UNDEFINED = 0,
  REFERENCE_TYPE_USAGE = 1,
  REFERENCE_USAGE = 2,
  REFERENCE_CALL = 3,
  REFERENCE_INHERITANCE = 4,
  REFERENCE_OVERRIDE = 5,
  REFERENCE_TYPE_ARGUMENT = 6,
  REFERENCE_TEMPLATE_SPECIALIZATION = 7,
  REFERENCE_INCLUDE = 8,
  REFERENCE_IMPORT = 9,
  REFERENCE_MACRO_USAGE = 10,
  REFERENCE_ANNOTATION_USAGE = 11
};

ReferenceKind intToReferenceKind(int v);
int referenceKindToInt(ReferenceKind t);
