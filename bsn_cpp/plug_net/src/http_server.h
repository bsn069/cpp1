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
	virtual I_Address::T_SPI_Address GetAddress() override;
	virtual void SetAddress(I_Address::T_SPI_Address spI_Address) override;
	virtual bool Start() override;
	virtual bool Stop() override;

public:
	static T_SPC_HttpServer NewC_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_HttpServer NewI_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
 
 	T_SPC_HttpServer GetSPC_HttpServer();
	void RunCoroutineImp(boost::asio::yield_context yield);

public:
	C_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_HttpServer();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
	boost::asio::io_service& m_IOService;
	boost::asio::ip::tcp::acceptor m_Acceptor;

	I_Address::T_SPI_Address m_spI_Address;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End