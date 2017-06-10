#include "./../interface.h"
#include "./../log.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
static char const * const sc_logLevel2Color[] = {
	"\033[40;31m",
	"\033[40;33m",
	"\033[40;32m",
};
static char const * const sc_endColor = "\033[0m";
 
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
	D_LogInfoFmt("Name()=%s", this->Name());
}


C_Interface::~C_Interface()
{
	D_LogInfoFmt("Name()=%s", this->Name());
	SetLib(nullptr);
}


void C_Interface::InitLog()
{
	m_pLog = CreateLog(Name(), this);
}


void C_Interface::WaitQuit() 
{
	D_LogInfoFmt("Name()=%s", this->Name());
	m_pLog = nullptr;
}

void C_Interface::Print(uint32_t uLogLevel, const char * strInfo)
{
	fprintf(stdout, "%s%s%s", sc_logLevel2Color[uLogLevel], strInfo, sc_endColor);
}


I_Log::T_SharePtr C_Interface::CreateLog(char const * const strName, void* pOwner)
{
	D_LogInfoFmt("strName=%s", this->Name());

	char buffer[4096];
    snprintf(
        buffer
		, D_ArrayCount(buffer)
		, "%s_%p"
		, strName
		, pOwner
    );
	
	auto pSelf = shared_from_this();
	auto pSelfC = std::dynamic_pointer_cast<C_Interface>(pSelf);
 	auto p = I_Log::T_SharePtr(New<C_Log>(pSelfC, buffer), [](C_Log* pLog){Delete(pLog);});

	D_LogInfoFmt("addr=0x%X", p.get());
	return p;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
