#include "alloc_raw.h"

#include <bsn_cpp/common/include/port.h>
#include <bsn_cpp/load_lib/include/port.h>
#include <bsn_cpp/log/include/port.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/asio.hpp>

#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
	boost::asio::io_service ioService;

	auto iCommon = D_N1(common)::NewCommon();
	std::cout << "iCommon=" << iCommon << std::endl;

	auto pAllocRaw = iCommon->NewAlloc(D_N1(common)::I_Alloc::Raw);
	std::cout << "pAllocRaw=" << pAllocRaw << std::endl;
	iCommon->SetGlobalAlloc(pAllocRaw);

	auto iLoadLib = D_N1(load_lib)::NewLoadLib();
	std::cout << "iLoadLib=" << iLoadLib << std::endl;

	D_N1(log)::I_Log::T_SPI_Log iLog = nullptr;
	{
		auto pLib = iLoadLib->Load("log", "bsn_dlib_log", "_d", "");
		auto pFuncNewLog = (D_N1(log)::NewLog)(pLib->Func("NewLog"));
		iLog = pFuncNewLog(pLib);
		std::cout << "iLog=" << iLog << std::endl;

		iLoadLib->SetLog(iLog);
	}

	D_N1(net)::I_Net::T_SPI_Net iNet = nullptr;
	{
		auto pLib = iLoadLib->Load("net", "bsn_dlib_net", "_d", "");
		auto pFuncNewNet = (D_N1(net)::NewNet)(pLib->Func("NewNet"));
		iNet = pFuncNewNet(pLib, ioService);
		std::cout << "iNet=" << iNet << std::endl;

		iNet->SetLog(iLog);
		iNet->SetCommon(iCommon);
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));
	ioService.run();
	
	iNet.WaitQuit();
	iNet = nullptr;

	iLog = nullptr;
	iLoadLib.WaitQuit();
	iLoadLib = nullptr;

	pAllocRaw = nullptr;
	iCommon = nullptr;

	std::this_thread::sleep_for(std::chrono::seconds(5));
}
