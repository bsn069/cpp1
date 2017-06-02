#include "./../interface.h"
#include <stdio.h>
#include <stdarg.h>
D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

const char SetBackgroundColor_Red[] = "\033[41m\033[37m";
const char SetBackgroundColor_Green[] = "\033[42m\033[37m";
const char SetBackgroundColor_Yellow[] = "\033[43m\033[30m";
const char SetFontColor_Green[] = "\033[32m\033[40m";
const char ResetConsolasStyle[] = "\033[0m";

wchar_t const* const C_Interface::Error(int32_t const i32ErrorCode) const
{
	switch (i32ErrorCode)
	{
		case 1: return L"1";
		default: return L"Unknown";
	}
}


wchar_t const* const C_Interface::Name() const
{
	return L"log";
}


C_Interface::C_Interface()
{
 
}


C_Interface::~C_Interface()
{
 
}

void C_Interface::Info(const char * strInfo)
{
	fprintf(stdout, SetFontColor_Green);
	this->Print(strInfo);
}

void C_Interface::Warn(const char * strInfo)
{
	fprintf(stdout, SetBackgroundColor_Yellow);
	this->Print(strInfo);
}

void C_Interface::Error(const char * strInfo)
{
	fprintf(stdout, SetBackgroundColor_Red);
	this->Print(strInfo);
}

void C_Interface::Print(const char * strInfo)
{
	fprintf(stdout, "%s\n", strInfo);
	fprintf(stdout, "\r\n%s", ResetConsolasStyle);
}


void C_Interface::InfoFmt(const char * strFormat, ...)
{
	fprintf(stdout, SetFontColor_Green);

	va_list args;
	va_start(args, strFormat);
	this->FmtPrint(strFormat, args);
	va_end(args);
}

void C_Interface::WarnFmt(const char * strFormat, ...)
{
 	fprintf(stdout, SetBackgroundColor_Yellow);

	va_list args;
	va_start(args, strFormat);
	this->FmtPrint(strFormat, args);
	va_end(args);
}

void C_Interface::ErrorFmt(const char * strFormat, ...)
{
 	fprintf(stdout, SetBackgroundColor_Red);

	va_list args;
	va_start(args, strFormat);
	this->FmtPrint(strFormat, args);
	va_end(args);
}

void C_Interface::FmtPrint(const char * strFormat, ...)
{
	va_list args;
	va_start(args, strFormat);
	vfprintf(stdout, strFormat, args);
	va_end(args);
	fprintf(stdout, "\r\n%s", ResetConsolasStyle);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
