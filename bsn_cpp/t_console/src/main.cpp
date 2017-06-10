#include <bsn_cpp/lib_loader/include/port.h>
#include <bsn_cpp/log/include/i_interface.h>
#include <bsn_cpp/console_input/include/i_interface.h>

#include <boost/program_options.hpp>
#include <stdint.h>
#include <locale.h>
#include <iostream>
#include <vector>

int 
main(int argc, char* argv[])
{
	// setlocale(LC_ALL, "chs"); 

	{
		auto pLibLoader = D_N1(lib_loader)::Create();
		std::cout << "pLibLoader=" << pLibLoader << std::endl;

		D_N1(log)::I_Interface::T_SharePtr pLogInterface = nullptr;
		{
			pLibLoader->Load("log", "bsn_dlib_log", "_d", "");
			auto pLib = pLibLoader->Get("log");
			auto pFuncCreate = (D_N1(log)::T_FuncCreate)(pLib->Func("Create"));
			pLogInterface = pFuncCreate(pLib);
		}

		{
			auto pLog = pLogInterface->CreateLog("lib_loader", pLibLoader.get());
			pLibLoader->SetLog(pLog);
		}

		pLogInterface->WaitQuit();
		{
			pLibLoader->Load("log", "bsn_dlib_log", "_d", "");
			auto pLib = pLibLoader->Get("log");
			auto pFuncCreate = (D_N1(log)::T_FuncCreate)(pLib->Func("Create"));
			pLogInterface = pFuncCreate(pLib);
		}

		pLogInterface->WaitQuit();
		pLogInterface = nullptr;
		pLibLoader->WaitQuit();
	}

	std::cout << "要退出了" << std::endl;
	// int t;
	// std::cin >> t;
	return 0;
}









