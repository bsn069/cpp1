#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include "./interface.h"
#include <bsn_cpp/lib_loader/include/port.h>
#include <bsn_cpp/log/include/i_interface.h>
#include <bsn_cpp/console_input/include/i_interface.h>

#include <boost/program_options.hpp>
#include <stdint.h>
#include <locale.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

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

D_FunImp D_DllCExport int Run(int argc, char* argv[])
{
	// setlocale(LC_ALL, "chs"); 

	{
		auto pLibLoader = D_N1(lib_loader)::Create();
		std::cout << "pLibLoader=" << pLibLoader << std::endl;

		D_N1(log)::I_Interface::T_SharePtr pLogInterface = nullptr;
		{
			auto pLib = pLibLoader->Load("log", "bsn_dlib_log", "_d", "");
			auto pFuncCreate = (D_N1(log)::T_FuncCreate)(pLib->Func("Create"));
			pLogInterface = pFuncCreate(pLib);
		}

		// main log
		auto m_pLog = pLogInterface->CreateLog("main", nullptr);

		{
			auto pLog = pLogInterface->CreateLog(pLibLoader->Name(), pLibLoader.get());
			pLibLoader->SetLog(pLog);
		}

		D_N1(console_input)::I_Interface::T_SharePtr pConsoleInputInterface = nullptr;
		{
			auto pLib = pLibLoader->Load("console_input", "bsn_dlib_console_input", "_d", "");
			auto pFuncCreate = (D_N1(console_input)::T_FuncCreate)(pLib->Func("Create"));
			pConsoleInputInterface = pFuncCreate(pLib);
			auto pLog = pLogInterface->CreateLog(pConsoleInputInterface->Name(), pConsoleInputInterface.get());
			pConsoleInputInterface->SetLog(pLog);
			pConsoleInputInterface->Start();
		}

		{
			D_LogInfo("make input thread");
			auto inputThread = std::thread(ThreadInput);
			inputThread.detach();
		}
		std::this_thread::sleep_for(std::chrono::seconds(10));

		pConsoleInputInterface->WaitQuit();
		pConsoleInputInterface = nullptr;

		m_pLog = nullptr;
		pLogInterface->WaitQuit();
		pLogInterface = nullptr;

		pLibLoader->WaitQuit();
		pLibLoader = nullptr;
	}

	std::cout << "要退出了" << std::endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
