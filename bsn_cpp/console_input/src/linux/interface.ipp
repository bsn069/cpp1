#include "./../interface.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <chrono>
#include <iostream>
#include <stdio.h>
D_BsnNamespace1(console_input)
//////////////////////////////////////////////////////////////////////

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
	return "console_input";
}


C_Interface::C_Interface()
: m_lib(nullptr)
, m_bQuit(false)
, m_bStart(false)
{
	D_LogInfoFmt("Name()=%s", this->Name());
}


C_Interface::~C_Interface()
{
	D_LogInfoFmt("Name()=%s", this->Name());
	SetLib(nullptr);
}

void C_Interface::SetLib(T_SharePtrLib lib) 
{
	m_lib = lib;
}

void C_Interface::Start() 
{
	D_LogInfo("start");
	
	if (m_bStart)
	{
		D_LogError("had start");
		return;
	}
	m_bStart = true;
}


void C_Interface::WaitQuit() 
{
	D_LogInfo("wait quit");

	if (!m_bStart)
	{
		D_LogError("not start");
		return;
	}
	m_bQuit = true; 
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
