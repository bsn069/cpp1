#pragma once

#include <bsn_cpp/plug_net/include/i_http_server.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_HttpServer : public I_HttpServer {
public:
	typedef std::shared_ptr<C_HttpServer> T_SPC_HttpServer;	

public: // I_HttpServer
 

public:
	static T_SPC_HttpServer NewC_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_HttpServer NewI_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
 
public:
	C_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_HttpServer();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End