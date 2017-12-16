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


D_FunImp D_DllCExport int Run(int argc, char* argv[])
{
	// setlocale(LC_ALL, "chs"); 

	C_Interface::T_SharePtr pGlobal(New<C_Interface>(), Delete<C_Interface>);
	pGlobal->Start(argc, argv);	
	return 0;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
