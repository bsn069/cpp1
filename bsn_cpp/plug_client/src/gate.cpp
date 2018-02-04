#include <bsn_cpp/plug_client/src/gate.h>
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

//////////////////////////////////////////////////////////////////////
C_Gate* CreateC_Gate(C_PlugClient::T_SPC_PlugClient spC_PlugClient) {
	D_OutInfo();
	C_Gate* pC_Gate = New<C_Gate>(spC_PlugClient);
	return pC_Gate;
}

void ReleaseC_Gate(I_Gate* pI_Gate) {
	D_OutInfo();
	C_Gate* pC_Gate = static_cast<C_Gate*>(pI_Gate);
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