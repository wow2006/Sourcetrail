#ifndef ERROR_COUNT_INFO_H
#define ERROR_COUNT_INFO_H

#include "ErrorInfo.h"

struct ErrorCountInfo
{
	ErrorCountInfo(): total(0), fatal(0) {}

	ErrorCountInfo(size_t total_, size_t fatal_): total(total_), fatal(fatal_) {}

	ErrorCountInfo(const std::vector<ErrorInfo>& errors): total(0), fatal(0)
	{
		for (const ErrorInfo& error: errors)
		{
			total++;

			if (error.fatal)
			{
				fatal++;
			}
		}
	}

	size_t total;
	size_t fatal;
};

#endif	  // ERROR_COUNT_INFO_H
