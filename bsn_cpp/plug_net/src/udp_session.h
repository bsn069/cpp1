#pragma once

#include <bsn_cpp/plug_net/include/i_udp_session.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_UDPSession : public I_UDPSession {
public:
	typedef std::shared_ptr<C_UDPSession>   T_SPC_UDPSession;	
	typedef boost::asio::ip::udp::socket    T_Socket;

public: // I_UDPSession
	virtual I_Address::T_SPI_Address    GetAddress() override;
	virtual bool    SendTo(I_Address::T_SPI_Address spI_Address, uint8_t* pData, uint32_t u32Len) override;

public:
	static T_SPC_UDPSession NewC_UDPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet, I_Address::T_SPI_Address spI_Address);
	static T_SPI_UDPSession NewI_UDPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet, I_Address::T_SPI_Address spI_Address);
 
 	T_SPC_UDPSession    GetSPC_UDPSession();
	T_Socket&           GetSocket();

public:
	C_UDPSession(C_PlugNet::T_SPC_PlugNet spC_PlugNet, I_Address::T_SPI_Address spI_Address);
	virtual ~C_UDPSession();

public:
	C_PlugNet::T_SPC_PlugNet        m_spC_PlugNet;
	I_Address::T_SPI_Address        m_spI_Address;
	C_UDPSession::T_Socket          m_Socket;
    boost::asio::ip::udp::endpoint  m_remoteEndPoint;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End