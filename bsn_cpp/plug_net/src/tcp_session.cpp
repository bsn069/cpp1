#include <bsn_cpp/plug_net/src/tcp_session.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_TCPSession::C_TCPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet)
	: m_spC_PlugNet(spC_PlugNet)
	, m_Socket(spC_PlugNet->GetSPI_PlugMgr()->GetIOService())
	, m_eState(I_TCPSession::E_State_Null)
	, m_eType(I_TCPSession::E_Type_Null) {

};

C_TCPSession::~C_TCPSession() {
	D_OutInfo();
	m_spC_PlugNet = nullptr;
}

C_TCPSession::T_SPC_TCPSession C_TCPSession::GetSPC_TCPSession() {
	D_OutInfo();
	auto spI_TCPSession = GetSPI_TCPSession();
	auto spC_TCPSession = std::dynamic_pointer_cast<C_TCPSession>(spI_TCPSession);
	return spC_TCPSession;
}

I_TCPSession::T_Socket& C_TCPSession::GetSocket() {
	 return m_Socket; 
}

void C_TCPSession::SetState(I_TCPSession::E_State eState) { 
	m_eState = eState; 
}

I_TCPSession::E_State C_TCPSession::GetState() const {
	return m_eState; 
}

void C_TCPSession::SetType(I_TCPSession::E_Type eType) {
	m_eType = eType; 
}

I_TCPSession::E_Type C_TCPSession::GetType() const {
	return m_eType; 
}
//////////////////////////////////////////////////////////////////////
C_TCPSession* CreateC_TCPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_TCPSession* pC_TCPSession = New<C_TCPSession>(spC_PlugNet);
	return pC_TCPSession;
}

void ReleaseC_TCPSession(I_TCPSession* pI_TCPSession) {
	D_OutInfo();
	C_TCPSession* pC_TCPSession = static_cast<C_TCPSession*>(pI_TCPSession);
	Delete(pC_TCPSession);
}

C_TCPSession::T_SPC_TCPSession C_TCPSession::NewC_TCPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_TCPSession = CreateC_TCPSession(spC_PlugNet);
	auto spC_TCPSession = C_TCPSession::T_SPC_TCPSession(pC_TCPSession, ReleaseC_TCPSession);
	return spC_TCPSession;
}

C_TCPSession::T_SPI_TCPSession C_TCPSession::NewI_TCPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_TCPSession = C_TCPSession::NewC_TCPSession(spC_PlugNet);
	auto spI_TCPSession = spC_TCPSession->GetSPI_TCPSession();
	return spI_TCPSession;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif