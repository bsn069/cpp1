#include "./../log.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <chrono>
#include <ctime>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

static char const * const sc_logLevel2Color[] = {
	"\033[40;32m",
	"\033[40;32m",
	"\033[40;33m",
	"\033[40;31m",
};
static char const * const sc_endColor = "\033[0m";

void C_Log::UpdateTime() {
	using std::chrono::system_clock;
	auto nowTime = system_clock::now();
	std::time_t tt = system_clock::to_time_t( nowTime );
	struct tm* ptm = localtime(&tt);
 
	static int const freeSize = (int)D_ArrayCount(m_pszTime) - 1;
	int length = strftime(
        m_pszTime 
		, freeSize
		, "%Y-%m-%d %H:%M:%S"
		, ptm
	);

    if (length > freeSize) {
    	length = freeSize;
    } else if (length < 0) {
        length = 0;  
    }
    m_pszTime[length++] = '\0';
}

void C_Log::FmtPrint(
	I_Log::E_Level eLevel
	, char const * strFile
	, uint32_t u32Line
	, char const * strFunc
	, const char * strFormat
	, va_list args
) {
	char buffer[4096];

    static int const freeSize = (int)D_ArrayCount(buffer) - 2;
    int length = vsnprintf(
		buffer
		, freeSize
		, strFormat
		, args
	);

    if (length > freeSize) {
    	length = freeSize;
    } else if (length < 0) {
        length = 0;  
    }
    buffer[length++] = '\n';
    buffer[length]   = '\0';

	Print(eLevel, strFile, u32Line, strFunc, buffer);	
}

void C_Log::Print(
	I_Log::E_Level eLevel
	, char const * strFile
	, uint32_t u32Line
	, char const * strFunc
	, char const * strInfo
) {
	UpdateTime();

	fprintf(
		stdout
		, "%s[%s|%s:%u(%s)]%s%s"
		, sc_logLevel2Color[eLevel]
		, m_pszTime
		, strFile ? strFile : ""
		, u32Line 
		, strFunc ? strFunc : ""
		, strInfo
		, sc_endColor
	);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End