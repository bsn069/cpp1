#include "global.h"

#include <bsn_cpp/common/include/lib_func.h>
#include <bsn_cpp/load_lib/include/lib_func.h>
#include <bsn_cpp/log/include/lib_func.h>
#include <bsn_cpp/sqlite/include/lib_func.h>
#include <bsn_cpp/net/include/lib_func.h>
#include <bsn_cpp/input/include/lib_func.h>
#include <bsn_cpp/log/include/d_log.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <bsn_cpp/include/name_space.h>

#include <boost/bind.hpp>

D_BsnNamespace1(global)
//////////////////////////////////////////////////////////////////////

C_Global::C_Global() 
	: m_u32FrameMS(1000)
	, m_updateTimer(m_ioService, boost::posix_time::millisec(1)) 
{
	m_bQuit = false;
}

C_Global::~C_Global() {
 
}

I_Global::T_SPI_Global
C_Global::GetSPI_Global() {
	return shared_from_this();
}

void C_Global::Init() {
	m_spI_Common = D_N1(common)::NewCommon();
	std::cout << "m_spI_Common=" << m_spI_Common << std::endl;

	m_spI_AllocRaw = m_spI_Common->NewAlloc(D_N1(common)::I_Alloc::Raw);
	std::cout << "m_spI_AllocRaw=" << m_spI_AllocRaw << std::endl;
	m_spI_Common->SetGlobalAlloc(m_spI_AllocRaw);

	m_spI_LoadLib = D_N1(load_lib)::NewLoadLib(shared_from_this());
	std::cout << "m_spI_LoadLib=" << m_spI_LoadLib << std::endl;

	{
		auto pLib = m_spI_LoadLib->Load("log", "bsn_dlib_log", "_d", "");
		auto pFunc = pLib->Func("NewLog");
		auto pFuncNewLog = (D_N1(log)::T_NewLog)pFunc;
		m_spI_Log = pFuncNewLog(pLib);
		D_LogInfoF(m_spI_Log, "m_spI_Log=%p", m_spI_Log.get())
	}
	{
		auto pLib = m_spI_LoadLib->Load("input", "bsn_dlib_input", "_d", "");
		auto pFunc = pLib->Func("NewInput");
		auto pFuncNewInput = (D_N1(input)::T_NewInput)pFunc;
		m_spI_Input = pFuncNewInput(pLib);
		D_LogInfoF(m_spI_Log, "m_spI_Input=%p", m_spI_Input.get())
	}
	{
		auto pLib = m_spI_LoadLib->Load("sqlite3", "bsn_dlib_sqlite", "_d", "");
		auto pFunc = pLib->Func("NewDB");
		auto pFuncNewDB = (D_N1(sqlite)::T_NewDB)pFunc;
		m_spI_Sqlite = pFuncNewDB(pLib, m_spI_Log);
		D_LogInfoF(m_spI_Log, "m_spI_Sqlite=%p", m_spI_Sqlite.get())
	}

	{
		auto pLib = m_spI_LoadLib->Load("net", "bsn_dlib_net", "_d", "");
		auto pFuncNewNet = (D_N1(net)::T_NewNet)(pLib->Func("NewNet"));
		m_spI_Net = pFuncNewNet(pLib, m_ioService);
		std::cout << "m_spI_Net=" << m_spI_Net << std::endl;

		m_spI_Net->SetLog(m_spI_Log);
		m_spI_Net->SetCommon(m_spI_Common);
	}
}

void 
C_Global::Start() {
	GetInput()->Start();
}

void 
C_Global::Quit() {
	GetInput()->Quit();
}

void C_Global::UnInit() {
 	m_spI_Net->WaitQuit();
	m_spI_Net = nullptr;

	m_spI_Input = nullptr;

	m_spI_Sqlite = nullptr;

	m_spI_Log = nullptr;
	m_spI_LoadLib->WaitQuit();
	m_spI_LoadLib = nullptr;

	m_spI_AllocRaw = nullptr;
	m_spI_Common = nullptr;
}

D_N1(common)::I_Common::T_SPI_Common
C_Global::GetCommon() {

	return m_spI_Common;
}

D_N1(common)::I_Alloc::T_SPI_Alloc
C_Global::GetAllocRaw() {
	return m_spI_AllocRaw;
}

D_N1(load_lib)::I_LoadLib::T_SPI_LoadLib
C_Global::GetLoadLib() {
	return m_spI_LoadLib;
}

D_N1(log)::I_Log::T_SPI_Log
C_Global::GetLog() {
	return m_spI_Log;
}

D_N1(input)::I_Input::T_SPI_Input
C_Global::GetInput() {
	return m_spI_Input;
}

D_N1(net)::I_Net::T_SPI_Net
C_Global::GetNet() {
	return m_spI_Net;
}

D_N1(sqlite)::I_DB::T_SPI_DB
C_Global::GetSqlite() {
	return m_spI_Sqlite;
}
		
D_FunImp I_Global* 
CreateCGlobal() {
	C_Global* imp = New<C_Global>();
	return imp;
}


D_FunImp void 
ReleaseCGlobal(I_Global* iGlobal) {
	C_Global* pImp = static_cast<C_Global*>(iGlobal);
	Delete(pImp);
}


I_Global::T_SPI_Global 
C_Global::NewI_Global() {
	auto spI_Global = I_Global::T_SPI_Global(
		CreateCGlobal()
		, ReleaseCGlobal
	);
	return spI_Global;
}

void C_Global::Run() {
	Init();
	Start();

	WaitUpdate();
	m_ioService.run();
	
	Quit();
	UnInit();
}

void 
C_Global::ProcCmd(std::string& strCmd) {
	D_LogInfoF(
		m_spI_Log
		, "C_Global::ProcCmd strCmd=%s"
		, strCmd.c_str()
	);

	if (strCmd.compare("quit") == 0) {
		m_bQuit = true;
	}
}

void 
C_Global::UpdateCmds() {
	auto pCmds = GetInput()->GetCmds();
	for (auto& strCmd : *pCmds) {
		ProcCmd(strCmd);
	}
}

void C_Global::Update(const boost::system::error_code& ec) {
	D_LogInfoF(
		m_spI_Log
		, "C_Global::Update ec=%s"
		, ec.message().c_str()
	);

	UpdateCmds();

	WaitUpdate();
}

void C_Global::WaitUpdate() {
	static auto s_updateFunc = boost::bind(
		&C_Global::Update
		, this
		, boost::asio::placeholders::error
	);

	if (m_bQuit) {
		return;
	}

	m_updateTimer.expires_at(m_updateTimer.expires_at() + boost::posix_time::millisec(m_u32FrameMS));

	m_updateTimer.async_wait(s_updateFunc);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 