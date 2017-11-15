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

void C_Log::FmtPrint(I_Log::E_Level eLevel, const char * strFormat, va_list args)
{
	char buffer[4096];
    int length = 0;
    int freeSize = 0;

	using std::chrono::system_clock;
	auto nowTime = system_clock::now();
	std::time_t tt = system_clock::to_time_t( nowTime );
	struct tm* ptm = localtime(&tt);
	
	freeSize = (int)D_ArrayCount(buffer) - length;
	length += strftime(
        buffer + length
		, freeSize
		, "[%Y-%m-%d %H:%M:%S]"
		, ptm
	);

    freeSize = (int)D_ArrayCount(buffer) - length;
    length += snprintf(
        buffer + length
		, freeSize
		, "[%s]"
		, sc_logLevel2Name[eLevel]
    );

    freeSize = (int)D_ArrayCount(buffer) - length - 2;
    int writeSize = vsnprintf(
		buffer + length
		, freeSize
		, strFormat
		, args
	);

    if (writeSize > freeSize) 
	{
    	writeSize = freeSize;
    }
    else if (writeSize < 0) 
	{
        writeSize = 0;  
    }

    length += writeSize;
    buffer[length++] = '\n';
    buffer[length]   = '\0';

	Print(eLevel, buffer);	
}

void C_Log::Print(I_Log::E_Level eLevel, char const * strInfo)
{
	fprintf(stdout, "%s%s%s", sc_logLevel2Color[eLevel], strInfo, sc_endColor);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End