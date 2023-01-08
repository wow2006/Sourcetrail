#pragma once

enum SourceGroupStatusType { SOURCE_GROUP_STATUS_ENABLED, SOURCE_GROUP_STATUS_DISABLED };

std::string sourceGroupStatusTypeToString(SourceGroupStatusType v);
SourceGroupStatusType stringToSourceGroupStatusType(std::string v);
