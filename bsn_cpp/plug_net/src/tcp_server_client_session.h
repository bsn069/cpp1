#pragma once

#include <bsn_cpp/plug_net/include/i_tcp_server_client_session.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_TCPServer;

class C_TCPServerClientSession : public I_TCPServerClientSession {
public:
	typedef std::shared_ptr<C_TCPServerClientSession> T_SPC_TCPServerClientSession;	
	typedef std::shared_ptr<C_TCPServer> T_SPC_TCPServer;

public: // I_TCPServerClientSession
 	virtual bool Start() override;
	virtual bool Stop() override;

public:
	static T_SPC_TCPServerClientSession NewC_TCPServerClientSession(T_SPC_TCPServer spC_TCPServer);
	static T_SPI_TCPServerClientSession NewI_TCPServerClientSession(T_SPC_TCPServer spC_TCPServer);
 
 	T_SPC_TCPServerClientSession GetSPC_TCPServerClientSession();
	void RunCoro(boost::asio::yield_context yield);

public:
	explicit C_TCPServerClientSession(T_SPC_TCPServer spC_TCPServer);
	virtual ~C_TCPServerClientSession();

public:
	T_SPC_TCPServer m_spC_TCPServer;
	boost::asio::ip::tcp::socket m_Socket;
	std::array<char, 8192> m_Buffer;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End