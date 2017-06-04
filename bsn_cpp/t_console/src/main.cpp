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

		std::vector<D_N1(lib_loader)::I_Interface::T_SharePtr> allLibLoader;
	{

		D_N1(log)::I_Interface::T_SharePtr pLog = nullptr;
		{
			auto pLibLoader = D_N1(lib_loader)::Create();
			allLibLoader.push_back(pLibLoader);
			std::cout << pLibLoader << std::endl;
			pLibLoader->Open("bsn_dlib_log", "_d", "", 0);
			auto pFuncCreate = (D_N1(log)::T_FuncCreate)(pLibLoader->Func("Create"));
			std::cout << "pFuncCreate=" << pFuncCreate << std::endl;
			if (pFuncCreate) {
				pLog = pFuncCreate(pLibLoader);
				std::cout << "pLog=" << pLog << std::endl;
				pLog->Info("info");
			}
		}


		// {
		// 	auto pLibLoader = D_N1(lib_loader)::Create();
		// 	std::cout << pLibLoader << std::endl;
		// 	pLibLoader->Open("bsn_dlib_console_input", "_d", "", 0);
		// 	auto pFuncCreate = (D_N1(console_input)::T_FuncCreate)(pLibLoader->Func("Create"));
		// 	std::cout << pFuncCreate << std::endl;
		// 	if (pFuncCreate) {
		// 		auto pService = pFuncCreate();
		// 		std::cout << pService << std::endl;
		// 	}
		// }
	}
		std::cout << "allLibLoader.clear()"  << std::endl;
		allLibLoader.clear();

	std::cout << "要退出了" << std::endl;
	int t;
	std::cin >> t;
	return 0;
}









