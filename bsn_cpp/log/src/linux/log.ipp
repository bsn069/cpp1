#include "./../log.h"
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <chrono>
#include <ctime>
D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
static char const * const sc_logLevel2Name[] = {
	"Error",
	"Warn",
	"Info"
};

char const * const C_Log::Name() const 
{
	return m_pstrName.c_str();
}


C_Log::C_Log(T_SharePtrCInterface pInterface, char const * const pstrName)
: m_pInterface(pInterface)
, m_logId(0)
, m_pstrName(pstrName)
{
	InfoFmt("C_Log::C_Log() %p", this);
}


C_Log::~C_Log()
{
	InfoFmt("C_Log::~C_Log() %p", this);
	m_pInterface = nullptr;
}

void C_Log::Info(const char * strInfo)
{
	m_pInterface->Print(2, strInfo);
}

void C_Log::Warn(const char * strInfo)
{
	m_pInterface->Print(1, strInfo);
}

void C_Log::Error(const char * strInfo)
{
	m_pInterface->Print(0, strInfo);
}

void C_Log::InfoFmt(const char * strFormat, ...)
{
	va_list args;
	va_start(args, strFormat);
	FmtPrint(2, strFormat, args);
	va_end(args);
}

void C_Log::WarnFmt(const char * strFormat, ...)
{
	va_list args;
	va_start(args, strFormat);
	FmtPrint(1, strFormat, args);
	va_end(args);
}

void C_Log::ErrorFmt(const char * strFormat, ...)
{
	va_list args;
	va_start(args, strFormat);
	FmtPrint(0, strFormat, args);
	va_end(args);
}

void C_Log::FmtPrint(uint32_t uLogLevel, const char * strFormat, va_list args)
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

	m_logId++;
    freeSize = (int)D_ArrayCount(buffer) - length;
    length += snprintf(
        buffer + length
		, freeSize
		, "[%s][%u][%s]"
		, Name()
		, m_logId
		, sc_logLevel2Name[uLogLevel]
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

	m_pInterface->Print(uLogLevel, buffer);	
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
