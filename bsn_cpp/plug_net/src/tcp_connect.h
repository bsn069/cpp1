#pragma once

#include <bsn_cpp/plug_net/include/i_tcp_connect.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_TCPConnect : public I_TCPConnect {
public:
	typedef std::shared_ptr<C_TCPConnect> T_SPC_TCPConnect;	

public: // I_TCPConnect
	virtual bool Connect(
		I_TCPSession::T_SPI_TCPSession spI_TCPSession
		, I_Address::T_SPI_Address spI_Address
		, T_FuncOnConnect func
	) override;
	virtual void ConnectCoro(
		boost::asio::yield_context yield
		, I_TCPSession::T_SPI_TCPSession spI_TCPSession
		, I_Address::T_SPI_Address spI_Address
		, T_FuncOnConnect func
	) override;
	virtual bool CanConnect(I_TCPSession::T_SPI_TCPSession spI_TCPSession) override;

public:
	static T_SPC_TCPConnect NewC_TCPConnect(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_TCPConnect NewI_TCPConnect(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
 
 	T_SPC_TCPConnect GetSPC_TCPConnect();

public:
	C_TCPConnect(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_TCPConnect();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
	boost::asio::io_service& m_IOService;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End