#include "alloc_raw.h"

#include <bsn_cpp/common/include/port.h>
#include <bsn_cpp/load_lib/include/port.h>
#include <bsn_cpp/log/include/port.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
	auto iCommon = D_N1(common)::Create();
	std::cout << "iCommon=" << iCommon << std::endl;

	auto pAllocRaw = iCommon->NewAlloc(D_N1(common)::I_Alloc::Raw);
	std::cout << "pAllocRaw=" << pAllocRaw << std::endl;
	iCommon->SetGlobalAlloc(pAllocRaw);

	auto iLoadLib = D_N1(load_lib)::Create();
	std::cout << "iLoadLib=" << iLoadLib << std::endl;

	D_N1(log)::I_Log::T_SPI_Log iLog = nullptr;
	{
		auto pLib = iLoadLib->Load("log", "bsn_dlib_log", "_d", "");
		auto pFuncCreate = (D_N1(log)::Create)(pLib->Func("Create"));
		iLog = pFuncCreate(pLib);
		std::cout << "iLog=" << iLog << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));

	iLog = nullptr;
	iLoadLib.WaitQuit();
	iLoadLib = nullptr;

	pAllocRaw = nullptr;
	iCommon = nullptr;

	std::this_thread::sleep_for(std::chrono::seconds(5));
}
