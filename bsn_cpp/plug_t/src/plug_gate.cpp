#include <bsn_cpp/plug_gate/src/plug_gate.h>

#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>
#include <bsn_cpp/plug_cmd/include/i_plug_cmd.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

#include <iostream>  
#include <string>  
#include <sstream>  

using namespace std;  

D_BsnNamespace1(plug_gate)
//////////////////////////////////////////////////////////////////////
C_PlugGate::C_PlugGate(void* pData) {
	D_OutInfo();
}

C_PlugGate::~C_PlugGate() {
	D_OutInfo();
 
}

char const * const C_PlugGate::GetName() const {
	return "gate";
}

bool C_PlugGate::Awake() {
	D_OutInfo();

	return true;
}

bool C_PlugGate::Init(T_SPI_PlugMgr spI_PlugMgr) {
	D_OutInfo();
	m_spI_PlugMgr = spI_PlugMgr;
	return true;
}

bool C_PlugGate::AllInitAfter() {
	D_OutInfo();

	RegAllCmd();
	
	return true;
}

bool C_PlugGate::RegAllCmd() {
	D_OutInfo();

	auto spI_PlugCmd = m_spI_PlugMgr->GetPlugPtr<D_N1(plug_cmd)::I_PlugCmd>("cmd");
	if (!spI_PlugCmd) {
		return false;
	}

	spI_PlugCmd->RegPlugCmd(GetName(), "help", boost::bind(&C_PlugGate::CmdHelp, this, _1, _2));

	return true;
}

void C_PlugGate::CmdHelp(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
}

bool C_PlugGate::Update() {
	// D_OutInfo();
	return true;
}

bool C_PlugGate::Quit() {
	D_OutInfo();
 
	return true;
}

bool C_PlugGate::UnInit() {
	D_OutInfo();
	m_spI_PlugMgr = nullptr;
	return true;
}

void C_PlugGate::OnReloadPre(std::string const& strName) {
	D_OutInfo();
	
}

void C_PlugGate::OnReloadPost(std::string const& strName) {
	D_OutInfo();
	
	if (strName.compare("cmd") == 0) {
		RegAllCmd();
	}
}

C_PlugGate::T_SPC_PlugGate C_PlugGate::GetSPC_PlugGate() {
	D_OutInfo();
	auto spI_Plug = GetSPI_Plug();
	auto spC_PlugGate = std::dynamic_pointer_cast<C_PlugGate>(spI_Plug);
	return spC_PlugGate;
}

//////////////////////////////////////////////////////////////////////
C_PlugGate* CreateC_PlugGate(void* pData) {
	D_OutInfo();
	C_PlugGate* pC_PlugGate = New<C_PlugGate>(pData);
	return pC_PlugGate;
}

void ReleaseC_PlugGate(I_PlugGate* pI_PlugGate) {
	D_OutInfo();
	C_PlugGate* pC_PlugGate = static_cast<C_PlugGate*>(pI_PlugGate);
	Delete(pC_PlugGate);
}

C_PlugGate::T_SPC_PlugGate C_PlugGate::NewC_PlugGate(void* pData) {
	D_OutInfo();
	auto pC_PlugGate = CreateC_PlugGate(pData);
	auto spC_PlugGate = C_PlugGate::T_SPC_PlugGate(pC_PlugGate, ReleaseC_PlugGate);
	return spC_PlugGate;
}

C_PlugGate::T_SPI_PlugGate C_PlugGate::NewI_PlugGate(void* pData) {
	D_OutInfo();
	auto spC_PlugGate = C_PlugGate::NewC_PlugGate(pData);
	auto spI_PlugGate = spC_PlugGate->GetSPI_PlugGate();
	return spI_PlugGate;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif