#pragma once

#include <bsn_cpp/plug_net/include/i_tcp_server.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_TCPServerClientSession;

class C_TCPServer : public I_TCPServer {
public:
	typedef std::shared_ptr<C_TCPServer> T_SPC_TCPServer;	
	typedef std::shared_ptr<C_TCPServerClientSession> T_SPC_TCPServerClientSession;	

public: // I_TCPServer
	virtual I_Address::T_SPI_Address GetAddress() override;
	virtual bool SetAddress(I_Address::T_SPI_Address spI_Address) override;

	virtual bool Start() override;
	virtual bool Stop() override;

	virtual bool StartListen() override;
	virtual bool StopListen() override;
	
	virtual bool StopAllClient() override;

public:
	static T_SPC_TCPServer NewC_TCPServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_TCPServer NewI_TCPServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
 
 	T_SPC_TCPServer GetSPC_TCPServer();

	bool StartListen();
	void ListenCoro(boost::asio::yield_context yield);

	bool StartSession(T_SPC_TCPServerClientSession session);
	bool StopSession(T_SPC_TCPServerClientSession session);

public:
	C_TCPServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_TCPServer();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
	boost::asio::io_service& m_IOService;
	boost::asio::ip::tcp::acceptor m_Acceptor;

	I_Address::T_SPI_Address m_spI_Address;
	std::set<T_SPC_TCPServerClientSession> m_ClientSessions;

	bool m_bListen;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End