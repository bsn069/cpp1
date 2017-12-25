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
	, m_bQuit(false)
{
 
}

C_Global::~C_Global() {
 
}

I_Global::T_SPI_Global
C_Global::GetSPI_Global() {
	return shared_from_this();
}

void 
C_Global::Awake() {
	D_OutInfo("enter global Awake");
	
	m_spI_Common = D_N1(common)::NewCommon();
	D_OutInfo(m_spI_Common.get());

	m_spI_AllocRaw = m_spI_Common->NewAlloc(D_N1(common)::I_Alloc::Raw);
	D_OutInfo(m_spI_AllocRaw.get());
	m_spI_Common->SetGlobalAlloc(m_spI_AllocRaw);

	m_spI_LoadLib = D_N1(load_lib)::NewLoadLib(GetSPI_Global());
	D_OutInfo(m_spI_LoadLib.get());

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

	D_LogInfo(m_spI_Log, "leave global Awake");
}


void C_Global::Init() {
	D_LogInfo(m_spI_Log, "enter global Init");

	D_LogInfo(m_spI_Log, "begin log Init");
	m_spI_Log->Init();
	D_LogInfo(m_spI_Log, "begin log Init");

	D_LogInfo(m_spI_Log, "begin input Init");
	m_spI_Input->Init();
	D_LogInfo(m_spI_Log, "begin input Init");

	D_LogInfo(m_spI_Log, "begin load lib Init");
	m_spI_LoadLib->Init();
	D_LogInfo(m_spI_Log, "begin load lib Init");

	D_LogInfo(m_spI_Log, "leave global Init");
}

void 
C_Global::Start() {
	D_LogInfo(m_spI_Log, "enter global start");
	
	D_LogInfo(m_spI_Log, "begin log start");
	m_spI_Log->Start();
	D_LogInfo(m_spI_Log, "end log start");

	D_LogInfo(m_spI_Log, "begin input start");
	m_spI_Input->Start();
	D_LogInfo(m_spI_Log, "end input start");

	D_LogInfo(m_spI_Log, "begin load lib start");
	m_spI_LoadLib->Start();
	D_LogInfo(m_spI_Log, "end load lib start");

	D_LogInfo(m_spI_Log, "leave global start");
}

void 
C_Global::Quit() {
	D_LogInfo(m_spI_Log, "enter global quit");

	D_LogInfo(m_spI_Log, "begin log quit");
	m_spI_Log->Quit();
	D_LogInfo(m_spI_Log, "end log quit");

	D_LogInfo(m_spI_Log, "begin input quit");
	m_spI_Input->Quit();
	D_LogInfo(m_spI_Log, "end input quit");

	D_LogInfo(m_spI_Log, "begin load lib quit");
	m_spI_LoadLib->Quit();
	D_LogInfo(m_spI_Log, "end load lib quit");

	D_LogInfo(m_spI_Log, "leave global quit");
}

void C_Global::UnInit() {
	D_LogInfo(m_spI_Log, "enter global UnInit");
 
	D_LogInfo(m_spI_Log, "begin input UnInit");
	m_spI_Input->UnInit();
	D_LogInfo(m_spI_Log, "end input UnInit");
	m_spI_Input = nullptr;

	D_LogInfo(m_spI_Log, "begin log UnInit");
	m_spI_Log->UnInit();
	D_LogInfo(m_spI_Log, "end log UnInit");
	m_spI_Log = nullptr;

	D_LogInfo(m_spI_Log, "begin load lib UnInit");
	m_spI_LoadLib->UnInit();
	D_LogInfo(m_spI_Log, "end load lib UnInit");
	m_spI_LoadLib = nullptr;

	m_spI_AllocRaw 	= nullptr;
	m_spI_Common 	= nullptr;

	D_LogInfo(m_spI_Log, "leave global UnInit");
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
		D_LogInfo(m_spI_Log, "in quit");
		return;
	}

	m_updateTimer.expires_at(m_updateTimer.expires_at() + boost::posix_time::millisec(m_u32FrameMS));

	m_updateTimer.async_wait(s_updateFunc);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 