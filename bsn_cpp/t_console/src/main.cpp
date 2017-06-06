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
		std::cout << pLibLoader << std::endl;

		D_N1(log)::I_Interface::T_SharePtr pLog = nullptr;
		{
			pLibLoader->Load("log", "bsn_dlib_log", "_d", "");
			auto pLib = pLibLoader->Get("log");
			auto pFuncCreate = (D_N1(log)::T_FuncCreate)(pLib->Func("Create"));
			std::cout << "pFuncCreate=" << pFuncCreate << std::endl;
			if (pFuncCreate) {
				pLog = pFuncCreate(pLib);
				std::cout << "pLog=" << pLog << std::endl;
				pLog->Info("info");
			}
		}
		pLibLoader->SetLog(pLog);

		{
			pLibLoader->Load("log", "bsn_dlib_log", "_d", "");
			auto pLib = pLibLoader->Get("log");
			auto pFuncCreate = (D_N1(log)::T_FuncCreate)(pLib->Func("Create"));
			std::cout << "pFuncCreate=" << pFuncCreate << std::endl;
			if (pFuncCreate) {
				pLog = pFuncCreate(pLib);
				std::cout << "pLog=" << pLog << std::endl;
				pLog->Info("info");
			}
		}

		pLog = nullptr;
		pLibLoader->WaitQuit();
	}

	std::cout << "要退出了" << std::endl;
	int t;
	std::cin >> t;
	return 0;
}









