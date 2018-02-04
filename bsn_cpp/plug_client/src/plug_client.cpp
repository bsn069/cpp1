#include <bsn_cpp/plug_client/src/plug_client.h>

#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>
#include <bsn_cpp/plug_net/include/i_plug_net.h>
#include <bsn_cpp/plug_net/include/i_tcp_session.h>
#include <bsn_cpp/plug_cmd/include/i_plug_cmd.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

#include <iostream>  
#include <string>  
#include <sstream>  

using namespace std;  

D_BsnNamespace1(plug_client)
//////////////////////////////////////////////////////////////////////
C_PlugClient::C_PlugClient(void* pData) {
	D_OutInfo();
}

C_PlugClient::~C_PlugClient() {
	D_OutInfo();
 
}

char const * const C_PlugClient::GetName() const {
	return "gate";
}

bool C_PlugClient::Awake() {
	D_OutInfo();

	return true;
}

bool C_PlugClient::Init(T_SPI_PlugMgr spI_PlugMgr) {
	D_OutInfo();
	m_spI_PlugMgr = spI_PlugMgr;
	return true;
}

bool C_PlugClient::AllInitAfter() {
	D_OutInfo();

	RegAllCmd();
	
	return true;
}

bool C_PlugClient::StartGate() {
	D_OutInfo();

	auto spI_PlugNet = m_spI_PlugMgr->GetPlugPtr<D_N1(plug_net)::I_PlugNet>("net");
	if (!spI_PlugNet) {
		return false;
	}

	auto spI_Address = spI_PlugNet->NewI_Address();
	spI_Address->SetAddr("localhost");
	spI_Address->SetPort(60001);

	m_spI_TCPListen = spI_PlugNet->NewI_TCPListen();
	m_spI_TCPListen->SetAddress(spI_Address);
	m_spI_TCPListen->SetFuncNew(
		boost::bind(&C_PlugClient::FuncNew, GetSPC_PlugClient())
	);
	m_spI_TCPListen->SetFuncOnAccept(
		boost::bind(&C_PlugClient::FuncOnAccept, GetSPC_PlugClient(), _1)
	);
	m_spI_TCPListen->StartListen();
	
	return true;
}

C_PlugClient::T_SPI_TCPSession C_PlugClient::FuncNew() {
	D_OutInfo();
	auto spI_PlugNet = m_spI_PlugMgr->GetPlugPtr<D_N1(plug_net)::I_PlugNet>("net");
	if (!spI_PlugNet) {
		return nullptr;
	}

	D_N1(plug_net)::I_TCPSession* pI_TCPSession = New<D_N1(plug_net)::I_TCPSession>(spI_PlugNet);
	T_SPI_TCPSession spI_TCPSession(pI_TCPSession);
	return spI_TCPSession;
}

void C_PlugClient::FuncOnAccept(T_SPI_TCPSession spI_TCPSession) {
	D_OutInfo();
	m_clientSessions.insert(spI_TCPSession);
}

bool C_PlugClient::RegAllCmd() {
	D_OutInfo();

	auto spI_PlugCmd = m_spI_PlugMgr->GetPlugPtr<D_N1(plug_cmd)::I_PlugCmd>("cmd");
	if (!spI_PlugCmd) {
		return false;
	}

	spI_PlugCmd->RegPlugCmd(GetName(), "help", boost::bind(&C_PlugClient::CmdHelp, this, _1, _2));

	return true;
}

void C_PlugClient::CmdHelp(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
}

bool C_PlugClient::Update() {
	// D_OutInfo();
	return true;
}

bool C_PlugClient::Quit() {
	D_OutInfo();

	m_spI_TCPListen->StopListen();
	m_clientSessions.clear();
 
	return true;
}

bool C_PlugClient::UnInit() {
	D_OutInfo();
	m_spI_TCPListen = nullptr;
	m_spI_PlugMgr = nullptr;
	return true;
}

void C_PlugClient::OnReloadPre(std::string const& strName) {
	D_OutInfo();
	
}

void C_PlugClient::OnReloadPost(std::string const& strName) {
	D_OutInfo();
	
	if (strName.compare("cmd") == 0) {
		RegAllCmd();
	}
}

C_PlugClient::T_SPC_PlugClient C_PlugClient::GetSPC_PlugClient() {
	D_OutInfo();
	auto spI_Plug = GetSPI_Plug();
	auto spC_PlugClient = std::dynamic_pointer_cast<C_PlugClient>(spI_Plug);
	return spC_PlugClient;
}

//////////////////////////////////////////////////////////////////////
C_PlugClient* CreateC_PlugClient(void* pData) {
	D_OutInfo();
	C_PlugClient* pC_PlugClient = New<C_PlugClient>(pData);
	return pC_PlugClient;
}

void ReleaseC_PlugClient(I_PlugClient* pI_PlugClient) {
	D_OutInfo();
	C_PlugClient* pC_PlugClient = static_cast<C_PlugClient*>(pI_PlugClient);
	Delete(pC_PlugClient);
}

C_PlugClient::T_SPC_PlugClient C_PlugClient::NewC_PlugClient(void* pData) {
	D_OutInfo();
	auto pC_PlugClient = CreateC_PlugClient(pData);
	auto spC_PlugClient = C_PlugClient::T_SPC_PlugClient(pC_PlugClient, ReleaseC_PlugClient);
	return spC_PlugClient;
}

C_PlugClient::T_SPI_PlugClient C_PlugClient::NewI_PlugClient(void* pData) {
	D_OutInfo();
	auto spC_PlugClient = C_PlugClient::NewC_PlugClient(pData);
	auto spI_PlugClient = spC_PlugClient->GetSPI_PlugClient();
	return spI_PlugClient;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif