#ifndef ERROR_COUNT_INFO_H
#define ERROR_COUNT_INFO_H

#include "ErrorInfo.h"

struct ErrorCountInfo
{
	ErrorCountInfo(): m_total(0), fatal(0) {}

	ErrorCountInfo(size_t total, size_t fatal): m_total(total), fatal(fatal) {}

	ErrorCountInfo(const std::vector<ErrorInfo>& errors): m_total(0), fatal(0)
	{
		for (const ErrorInfo& error: errors)
		{
			m_total++;

			if (error.fatal)
			{
				fatal++;
			}
		}
	}

	size_t m_total;
	size_t fatal;
};

#endif	  // ERROR_COUNT_INFO_H
