#pragma once

#include <bsn_cpp/plug_net/include/i_tcp_session.h>
#include <bsn_cpp/plug_net/src/plug_net.h>

#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_TCPSession : public I_TCPSession {
public:
	typedef std::shared_ptr<C_TCPSession> T_SPC_TCPSession;	

public: // I_TCPSession
	virtual I_TCPSession::T_Socket& GetSocket() override;

	virtual void SetState(I_TCPSession::E_State eState) override;
	virtual I_TCPSession::E_State GetState() const override;

	virtual void SetType(I_TCPSession::E_Type eType) override;
	virtual I_TCPSession::E_Type GetType() const override;

public:
	static T_SPC_TCPSession NewC_TCPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_TCPSession NewI_TCPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
 
 	T_SPC_TCPSession GetSPC_TCPSession();

public:
	C_TCPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_TCPSession();

protected:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
	I_TCPSession::T_Socket 	m_Socket;
	I_TCPSession::E_State 	m_eState;
	I_TCPSession::E_Type 		m_eType;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End