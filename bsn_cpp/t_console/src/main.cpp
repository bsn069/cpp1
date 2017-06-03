#include <bsn_cpp/lib_loader/include/port.h>
#include <bsn_cpp/log/include/i_interface.h>

#include <boost/program_options.hpp>
#include <stdint.h>
#include <locale.h>
#include <iostream>

int 
main(int argc, char* argv[])
{
	// setlocale(LC_ALL, "chs"); 

	{
		auto p = D_N1(lib_loader)::Create();
		std::cout << p << std::endl;
		p->Open("bsn_dlib_log", "_d", "", 0);
		auto pFuncCreate = (D_N1(log)::T_FuncCreate)(p->Func("Create"));
		std::cout << pFuncCreate << std::endl;
		if (pFuncCreate) {
			auto pLog = pFuncCreate();
			std::cout << pLog << std::endl;
			pLog->Info("info");
		}
	}

	std::cout << "要退出了" << std::endl;
	int t;
	std::cin >> t;
	return 0;
}









