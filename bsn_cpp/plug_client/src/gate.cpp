#include <bsn_cpp/plug_client/src/gate.h>
#include <bsn_cpp/plug_client/src/plug_client.h>

#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>
#include <bsn_cpp/plug_net/include/i_plug_net.h>
#include <bsn_cpp/plug_net/include/i_tcp_session.h>

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
C_Gate::C_Gate(C_PlugClient::T_SPC_PlugClient spC_PlugClient) 
	: m_spC_PlugClient(spC_PlugClient) {
	D_OutInfo();
}

C_Gate::~C_Gate() {
	D_OutInfo();
 
	m_spI_TCPSession = nullptr;
	m_spC_PlugClient = nullptr;
}

C_Gate::T_SPC_Gate C_Gate::GetSPC_Gate() {
	D_OutInfo();
	return shared_from_this();;
}

void C_Gate::OnConnect(T_SPI_TCPSession spI_TCPSession) {
	D_OutInfo();
}

bool C_Gate::Start() {
	D_OutInfo();

	auto spI_PlugNet = m_spC_PlugClient->GetSPI_PlugMgr()->GetPlugPtr<D_N1(plug_net)::I_PlugNet>("net");
	if (!spI_PlugNet) {
		return false;
	}

	// m_spI_TCPSession = spI_PlugNet->NewI_TCPSession();

	m_spI_Address = spI_PlugNet->NewI_Address();
	m_spI_Address->SetAddr("localhost");
	m_spI_Address->SetPort(60001);

	auto spI_TCPConnect = m_spC_PlugClient->GetSPI_TCPConnect();
	spI_TCPConnect->Connect(
		m_spI_TCPSession
		, spI_Address
		, boost::bind(&C_Gate::OnConnect, GetSPC_Gate(), _1)
	);
	
	return true;
}

//////////////////////////////////////////////////////////////////////
C_Gate* CreateC_Gate(C_PlugClient::T_SPC_PlugClient spC_PlugClient) {
	D_OutInfo();
	C_Gate* pC_Gate = New<C_Gate>(spC_PlugClient);
	return pC_Gate;
}

void ReleaseC_Gate(C_Gate* pC_Gate) {
	D_OutInfo();
	Delete(pC_Gate);
}

C_Gate::T_SPC_Gate C_Gate::NewC_Gate(C_PlugClient::T_SPC_PlugClient spC_PlugClient) {
	D_OutInfo();
	auto pC_Gate = CreateC_Gate(spC_PlugClient);
	auto spC_Gate = C_Gate::T_SPC_Gate(pC_Gate, ReleaseC_Gate);
	return spC_Gate;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif