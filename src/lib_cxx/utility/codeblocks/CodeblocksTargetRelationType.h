#pragma once

namespace Codeblocks {
enum TargetRelationType {
  CODEBLOCKS_TARGET_RELATION_IGNORE_TARGET,
  CODEBLOCKS_TARGET_RELATION_IGNORE_PROJECT,
  CODEBLOCKS_TARGET_RELATION_TARGET_BEFORE_PROJECT,
  CODEBLOCKS_TARGET_RELATION_TARGET_AFTER_PROJECT,
  CODEBLOCKS_TARGET_RELATION_UNKNOWN
};

int targetRelationTypeToInt(TargetRelationType v);
TargetRelationType intToTargetRelationType(int v);
}  // namespace Codeblocks
