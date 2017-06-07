#include "./../interface.h"
#include "./../log.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

const char SetBackgroundColor_Red[] = "\033[41m\033[37m";
const char SetBackgroundColor_Green[] = "\033[42m\033[37m";
const char SetBackgroundColor_Yellow[] = "\033[43m\033[30m";
const char SetFontColor_Green[] = "\033[32m\033[40m";
const char ResetConsolasStyle[] = "\033[0m";

void C_Interface::SetLib(T_SharePtrLib lib) {
	m_lib = lib;
}

char const* const C_Interface::Error(int32_t const i32ErrorCode) const
{
	switch (i32ErrorCode)
	{
		case 1: return "1";
		default: return "Unknown";
	}
}


char const* const C_Interface::Name() const
{
	return "log";
}


C_Interface::C_Interface()
: m_lib(nullptr)
{
  	std::cout << this->Name() << " C_Interface::C_Interface()" << std::endl;
}


C_Interface::~C_Interface()
{
	std::cout << this->Name() << " C_Interface::~C_Interface()" << std::endl;
	SetLib(nullptr);
	std::cout << this->Name() << " C_Interface::~C_Interface()1" << std::endl;
}


void C_Interface::FmtPrint(uint32_t uLogLevel, const char * strFormat, ...)
{
	char logInfo[2048];
	va_list args;
	va_start(args, strFormat);
	vsnprintf(logInfo, sizeof(logInfo), strFormat, args);
	va_end(args);
	
	Print(uLogLevel, logInfo);
}


void C_Interface::Print(uint32_t uLogLevel, const char * strInfo)
{
	auto color = SetBackgroundColor_Red;
	if (uLogLevel == 1)
	{
		color = SetBackgroundColor_Yellow;
	}
	else if (uLogLevel == 2)
	{
		color = SetFontColor_Green;
	}

	fprintf(stdout, color);
	fprintf(stdout, "%s\n", strInfo);
	fprintf(stdout, "%s", ResetConsolasStyle);
}


I_Log::T_SharePtr C_Interface::CreateLog()
{
	auto pSelf = shared_from_this();
	auto pSelfC = std::dynamic_pointer_cast<C_Interface>(pSelf);
 	auto p = I_Log::T_SharePtr(New<C_Log>(pSelfC), [](C_Log* pLog){Delete(pLog);});
	return p;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
