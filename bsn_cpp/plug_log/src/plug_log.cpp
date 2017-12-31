#include "plug_log.h"
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_log)
//////////////////////////////////////////////////////////////////////
C_PlugLog::C_PlugLog() {
	D_OutInfo();
	// m_ = reinterpret_cast<T_PlugData*>();
}

C_PlugLog::~C_PlugLog() {
	D_OutInfo();
 
}

bool C_PlugLog::Awake() {
	D_OutInfo();

	return true;
}

bool C_PlugLog::Init(T_SPI_PlugMgr spI_PlugMgr) {
	D_OutInfo();
	// m_spI_PlugMgr = spI_PlugMgr;
	return true;
}

bool C_PlugLog::AllInitAfter() {
	D_OutInfo();
	return true;
}

bool C_PlugLog::Update() {
	D_OutInfo();
	return true;
}

bool C_PlugLog::Quit() {
	D_OutInfo();
	return true;
}

bool C_PlugLog::UnInit() {
	D_OutInfo();
	// m_spI_PlugMgr = nullptr;
	return true;
}

void OnReloadPre(std::string const& strName) {
	D_OutInfo();
	
}

void OnReloadPost(std::string const& strName) {
	D_OutInfo();
	
}

void C_PlugLog::ProcCmd(std::string const& strCmd) {
	D_OutInfo1(strCmd);
 
}

C_PlugLog::T_SPC_PlugLog C_PlugLog::GetSPC_PlugLog() {
	D_OutInfo();
	auto spI_Plug = GetSPI_Plug();
	auto spC_PlugLog = std::dynamic_pointer_cast<C_PlugLog>(spI_Plug);
	return spC_PlugLog;
}


//////////////////////////////////////////////////////////////////////
C_PlugLog* CreateC_PlugLog() {
	D_OutInfo();
	C_PlugLog* pC_PlugLog = New<C_PlugLog>();
	return pC_PlugLog;
}

void ReleaseC_PlugLog(I_PlugLog* pI_PlugLog) {
	D_OutInfo();
	C_PlugLog* pC_PlugLog = static_cast<C_PlugLog*>(pI_PlugLog);
	Delete(pC_PlugLog);
}

C_PlugLog::T_SPC_PlugLog C_PlugLog::NewC_PlugLog() {
	D_OutInfo();
	auto pC_PlugLog = CreateC_PlugLog();
	auto spC_PlugLog = C_PlugLog::T_SPC_PlugLog(pC_PlugLog, ReleaseC_PlugLog);
	return spC_PlugLog;
}

C_PlugLog::T_SPI_PlugLog C_PlugLog::NewI_PlugLog() {
	D_OutInfo();
	auto spC_PlugLog = C_PlugLog::NewC_PlugLog();
	auto spI_PlugLog = spC_PlugLog->GetSPI_PlugLog();
	return spI_PlugLog;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif