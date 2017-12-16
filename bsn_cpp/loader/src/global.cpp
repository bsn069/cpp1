#include "global.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

#include <iostream>
#include <thread>

C_Global::C_Global()
	: m_u32FrameMS(1000)
	, m_updateTimer(m_ioService, boost::posix_time::millisec(m_u32FrameMS)) {

}

C_Global::~C_Global() {
	
}

void C_Global::Init() {
	m_spI_Common = D_N1(common)::NewCommon();
	std::cout << "m_spI_Common=" << m_spI_Common << std::endl;

	m_spI_AllocRaw = m_spI_Common->NewAlloc(D_N1(common)::I_Alloc::Raw);
	std::cout << "m_spI_AllocRaw=" << m_spI_AllocRaw << std::endl;
	m_spI_Common->SetGlobalAlloc(m_spI_AllocRaw);

	m_spI_LoadLib = D_N1(load_lib)::NewLoadLib();
	std::cout << "m_spI_LoadLib=" << m_spI_LoadLib << std::endl;

	{
		auto pLib = m_spI_LoadLib->Load("log", "bsn_dlib_log", "_d", "");
		auto pFunc = pLib->Func("NewLog");
		auto pFuncNewLog = (D_N1(log)::T_NewLog)pFunc;
		m_spI_Log = pFuncNewLog(pLib);
		std::cout << "m_spI_Log=" << m_spI_Log << std::endl;

		m_spI_LoadLib->SetLog(m_spI_Log);
	}
	{
		auto pLib = m_spI_LoadLib->Load("net", "bsn_dlib_net", "_d", "");
		auto pFuncNewNet = (D_N1(net)::T_NewNet)(pLib->Func("NewNet"));
		m_spI_Net = pFuncNewNet(pLib, m_ioService);
		std::cout << "m_spI_Net=" << m_spI_Net << std::endl;

		m_spI_Net->SetLog(m_spI_Log);
		m_spI_Net->SetCommon(m_spI_Common);
	}
	{
		auto pLib = m_spI_LoadLib->Load("sqlite3", "bsn_dlib_sqlite", "_d", "");
		auto pFunc = pLib->Func("NewDB");
		auto pFuncNewDB = (D_N1(sqlite)::T_NewDB)pFunc;
		m_spI_DB = pFuncNewDB(pLib, m_spI_Log);
		std::cout << "m_spI_DB=" << m_spI_DB << std::endl;
	}
}

void C_Global::UnInit() {
	m_spI_Net->WaitQuit();
	m_spI_Net = nullptr;

	m_spI_DB = nullptr;

	m_spI_Log = nullptr;
	m_spI_LoadLib->WaitQuit();
	m_spI_LoadLib = nullptr;

	m_spI_AllocRaw = nullptr;
	m_spI_Common = nullptr;
}

void C_Global::Run() {
	Init();

	WaitUpdate();
	m_ioService.run();
	
	UnInit();
}

void C_Global::Update(const boost::system::error_code& ec) {
	std::cout << "C_Global::Update=" << ec << std::endl;


	m_updateTimer.expires_at(m_updateTimer.expires_at() + boost::posix_time::millisec(m_u32FrameMS));
	WaitUpdate();
}

void C_Global::WaitUpdate() {
	static auto s_updateFunc = boost::bind(
		&C_Global::Update
		, this
		, boost::asio::placeholders::error
	);
	m_updateTimer.async_wait(s_updateFunc);
}
