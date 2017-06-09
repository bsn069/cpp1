#include "./../log.h"
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

char const* C_Log::Name() const 
{
	return "C_Log";
}


C_Log::C_Log(T_SharePtrCInterface pInterface)
: m_pInterface(pInterface)
{
  	std::cout << this->Name() << " C_Log::C_Log()" << std::endl;
}


C_Log::~C_Log()
{
	std::cout << this->Name() << " C_Log::~C_Log()" << std::endl;
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
    int writeSize = 0;
    int freeSize = 0;

    length = snprintf(
        buffer
		, D_ArrayCount(buffer)
		, "C_Log::FmtPrint[%u]: "
		, uLogLevel
    );

    freeSize = (int)D_ArrayCount(buffer) - length - sizeof("\n");
    writeSize = vsnprintf(buffer + length, freeSize, strFormat, args);
    if (writeSize <= 0 || writeSize >= freeSize) {
        writeSize = freeSize - 1;  
    }
    length += writeSize;
    buffer[length++] = '\n';
    buffer[length]   = '\0';

	m_pInterface->Print(uLogLevel, buffer);	
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
