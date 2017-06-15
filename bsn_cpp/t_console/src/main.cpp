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

int 
main(int argc, char* argv[])
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

		std::this_thread::sleep_for(std::chrono::seconds(10));

		pConsoleInputInterface->WaitQuit();
		pConsoleInputInterface = nullptr;

		pLogInterface->WaitQuit();
		pLogInterface = nullptr;

		pLibLoader->WaitQuit();
		pLibLoader = nullptr;
	}

	std::cout << "要退出了" << std::endl;
	int t;
	std::cin >> t;
	return 0;
}









