#include <bsn_cpp/load_lib/include/port.h>
#include <bsn_cpp/log/include/port.h>

#include <iostream>
#include <thread>

typedef D_FunDef D_N1(log)::I_Log::T_SPI_Log (*T_LogFuncCreate)(D_N1(load_lib)::I_Lib::T_SPI_Lib);

int main(int argc, char* argv[])
{
	auto iLoadLib = D_N1(load_lib)::Create();
	std::cout << "iLoadLib=" << iLoadLib << std::endl;

	D_N1(log)::I_Log::T_SPI_Log iLog = nullptr;
	{
		auto pLib = iLoadLib->Load("log", "bsn_dlib_log", "_d", "");
		auto pFuncCreate = (T_LogFuncCreate)(pLib->Func("Create"));
		iLog = pFuncCreate(pLib);
		std::cout << "iLog=" << iLog << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));

	iLog = nullptr;
	iLoadLib.WaitQuit();
	iLoadLib = nullptr;
}
