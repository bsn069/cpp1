#include <bsn_cpp/plug_net/src/udp_session.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_UDPSession::C_UDPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet, I_Address::T_SPI_Address spI_Address)
	: m_spC_PlugNet(spC_PlugNet)
    , m_spI_Address(spI_Address)
	, m_Socket(spC_PlugNet->GetSPI_PlugMgr()->GetIOService(), udp::endpoint(address::from_string(spI_Address->GetAddr(), spI_Address->GetPort()), )) {

};

C_UDPSession::~C_UDPSession() {
	D_OutInfo();
	m_spC_PlugNet = nullptr;
    m_spI_Address = nullptr;    
}

C_UDPSession::T_SPC_UDPSession C_UDPSession::GetSPC_UDPSession() {
	D_OutInfo();
	auto spI_UDPSession = GetSPI_UDPSession();
	auto spC_UDPSession = std::dynamic_pointer_cast<C_UDPSession>(spI_UDPSession);
	return spC_UDPSession;
}
 

I_Address::T_SPI_Address C_UDPSession::GetAddress() {
    return m_spI_Address;
}

bool C_UDPSession::SendTo(I_Address::T_SPI_Address spI_Address, uint8_t* pData, uint32_t u32Len) {
    return true;
}

//////////////////////////////////////////////////////////////////////
C_UDPSession* CreateC_UDPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_UDPSession* pC_UDPSession = New<C_UDPSession>(spC_PlugNet);
	return pC_UDPSession;
}

void ReleaseC_UDPSession(I_UDPSession* pI_UDPSession) {
	D_OutInfo();
	C_UDPSession* pC_UDPSession = static_cast<C_UDPSession*>(pI_UDPSession);
	Delete(pC_UDPSession);
}

C_UDPSession::T_SPC_UDPSession C_UDPSession::NewC_UDPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_UDPSession = CreateC_UDPSession(spC_PlugNet);
	auto spC_UDPSession = C_UDPSession::T_SPC_UDPSession(pC_UDPSession, ReleaseC_UDPSession);
	return spC_UDPSession;
}

C_UDPSession::T_SPI_UDPSession C_UDPSession::NewI_UDPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_UDPSession = C_UDPSession::NewC_UDPSession(spC_PlugNet);
	auto spI_UDPSession = spC_UDPSession->GetSPI_UDPSession();
	return spI_UDPSession;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 