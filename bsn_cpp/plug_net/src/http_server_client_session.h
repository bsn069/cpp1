#pragma once

#include <bsn_cpp/plug_net/include/i_http_server_client_session.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_HttpServer;

class C_HttpServerClientSession : public I_HttpServerClientSession {
public:
	typedef std::shared_ptr<C_HttpServerClientSession> T_SPC_HttpServerClientSession;	
	typedef std::shared_ptr<C_HttpServer> T_SPC_HttpServer;

public: // I_HttpServerClientSession
 	virtual bool Start() override;
	virtual bool Stop() override;

public:
	static T_SPC_HttpServerClientSession NewC_HttpServerClientSession(T_SPC_HttpServer spC_HttpServer, boost::asio::ip::tcp::socket Socket);
	static T_SPI_HttpServerClientSession NewI_HttpServerClientSession(T_SPC_HttpServer spC_HttpServer, boost::asio::ip::tcp::socket Socket);
 
 	T_SPC_HttpServerClientSession GetSPC_HttpServerClientSession();
	void RunCoroutineImp(boost::asio::yield_context yield);

public:
	explicit C_HttpServerClientSession(T_SPC_HttpServer spC_HttpServer, boost::asio::ip::tcp::socket Socket);
	virtual ~C_HttpServerClientSession();

public:
	T_SPC_HttpServer m_spC_HttpServer;
	boost::asio::ip::tcp::socket m_Socket;
	std::array<char, 8192> m_Buffer;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End