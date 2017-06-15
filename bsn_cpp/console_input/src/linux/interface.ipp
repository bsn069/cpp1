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
, m_pInputThread(nullptr)
, m_bQuit(false)
{
	D_LogInfoFmt("Name()=%s", this->Name());
}


C_Interface::~C_Interface()
{
	D_LogInfoFmt("Name()=%s", this->Name());
	SetLib(nullptr);
	m_pInputThread = nullptr;
}

void C_Interface::SetLib(T_SharePtrLib lib) 
{
	m_lib = lib;
}

void C_Interface::ThreadInput() 
{
	D_LogInfoFmt("input thread begin id=%u", std::this_thread::get_id());
	std::string strCmd;
	char cInput;

	while (!m_bQuit)
	{
		strCmd.clear();
		while ((cInput = getchar()) != '\n')
		{
			D_LogInfoFmt("input char = %c", cInput);
			strCmd += cInput;
		}

		D_LogInfoFmt("input %s", strCmd.c_str());
	}
	D_LogInfo("input thread end");
}

void C_Interface::Start() 
{
	D_LogInfo("start");
	
	if (m_pInputThread != nullptr)
	{
		D_LogError("had start");
		return;
	}

	m_pInputThread = New<std::thread>(&C_Interface::ThreadInput, this);
}


void C_Interface::WaitQuit() 
{
	D_LogInfo("wait quit");
	
	if (m_pInputThread != nullptr)
	{
		m_bQuit = true; 
		m_pInputThread->join();
		Delete(m_pInputThread);
		m_pInputThread = nullptr;
	}
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
