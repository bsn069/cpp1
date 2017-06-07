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
	char buffer[2048];

	va_list args;
	va_start(args, strFormat);
	vsnprintf(buffer, sizeof(buffer), strFormat, args);
	va_end(args);

	Info(buffer);
}

void C_Log::WarnFmt(const char * strFormat, ...)
{
	char buffer[2048];
	
	va_list args;
	va_start(args, strFormat);
	vsnprintf(buffer, sizeof(buffer), strFormat, args);
	va_end(args);

	Warn(buffer);
}

void C_Log::ErrorFmt(const char * strFormat, ...)
{
	char buffer[2048];
	
	va_list args;
	va_start(args, strFormat);
	vsnprintf(buffer, sizeof(buffer), strFormat, args);
	va_end(args);

	Error(buffer);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
