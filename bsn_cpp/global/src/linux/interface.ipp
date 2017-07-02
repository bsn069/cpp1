#include "./../interface.h"
#include <bsn_cpp/lib_loader/include/port.h>

#include <thread>

D_BsnNamespace1(global)
//////////////////////////////////////////////////////////////////////
void ThreadInput() 
{
	std::cout << "ThreadInput begin" << std::endl;

	std::string strCmd;
	char cInput;

	while (true)
	{
		strCmd.clear();
		while ((cInput = getchar()) != '\n')
		{
			// D_LogInfoFmt("input char = %c", cInput);
			strCmd += cInput;
		}
		std::cout << "input: " << strCmd << std::endl;
	}
		
	std::cout << "ThreadInput end" << std::endl;
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
	return "global";
}


C_Interface::C_Interface()
: m_bRun(false)
, m_pLog(nullptr)
, m_pLibLoader(nullptr)
, m_pLogInterface(nullptr)
{
	D_LogInfoFmt("Name()=%s", this->Name());
}


C_Interface::~C_Interface()
{
	D_LogInfoFmt("Name()=%s", this->Name());
	WaitQuit();
}


void C_Interface::WaitQuit()
{
	D_LogInfo("wait quit");
	
	if (!m_bRun)
	{
		D_LogError("not run");
		return;
	}	
	m_bRun = false;

	D_LogInfo("close all sub module log");
	{
		if (m_pLibLoader)
		{
			m_pLibLoader->SetLog(nullptr);		
		}
	}

	D_LogInfo("close all lib");
	{

		D_LogInfo("close log lib");
		m_pLog = nullptr;
		if (m_pLogInterface)
		{
			m_pLogInterface->WaitQuit();
			m_pLogInterface = nullptr;
		}

		if (m_pNetInterface)
		{
			m_pNetInterface->WaitQuit();
			m_pNetInterface = nullptr;
		}
	}

	D_LogInfo("close lib loader");
	if (m_pLibLoader)
	{
		m_pLibLoader->WaitQuit();
		m_pLibLoader = nullptr;
	}
}

void C_Interface::Loop() 
{
	D_LogInfo("loop");

	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void C_Interface::Start(int argc, char* argv[]) 
{
	D_LogInfo("start");

	if (m_bRun)
	{
		D_LogError("had run");
		return;
	}
	m_bRun = true;

	m_pLibLoader = D_N1(lib_loader)::Create();
	std::cout << "m_pLibLoader=" << m_pLibLoader << std::endl;

	{
		auto pLib = m_pLibLoader->Load("log", "bsn_dlib_log", "_d", "");
		auto pFuncCreate = (D_N1(log)::T_FuncCreate)(pLib->Func("Create"));
		m_pLogInterface = pFuncCreate(pLib);
		std::cout << "m_pLogInterface=" << m_pLogInterface << std::endl;
	}

	// main log
	m_pLog = m_pLogInterface->CreateLog(Name(), this);
	D_LogInfoFmt("this=%p", this);
	D_LogInfoFmt("m_pLog=%p", m_pLog.get());
	D_LogInfoFmt("m_pLibLoader=%p", m_pLibLoader.get());
	D_LogInfoFmt("m_pLogInterface=%p", m_pLogInterface.get());

	{
		D_LogInfo("set lib loader log");
		auto pLog = m_pLogInterface->CreateLog(m_pLibLoader->Name(), m_pLibLoader.get());
		m_pLibLoader->SetLog(pLog);
	}

	{
		auto pLib = m_pLibLoader->Load("net", "bsn_dlib_net", "_d", "");
		auto pFuncCreate = (D_N1(net)::T_FuncCreate)(pLib->Func("Create"));
		m_pNetInterface = pFuncCreate(pLib);
		D_LogInfoFmt("m_pNetInterface=%p", m_pLogInterface.get());
		auto pLog = m_pLogInterface->CreateLog(m_pNetInterface->Name(), m_pNetInterface.get());
		m_pNetInterface->SetLog(pLog);
		// auto p = m_pNetInterface->Create();
		// D_LogInfoFmt("p=%p", p.get());
		// m_pNetInterface->Release(p);
	}

	{
		D_LogInfo("make input thread");
		auto inputThread = std::thread(ThreadInput);
		inputThread.detach();
	}

	Loop();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
