#pragma once

#include <bsn_cpp/plug_net/include/i_http_client.h>

#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>


D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_HttpClient : public I_HttpClient {
public:
	typedef std::shared_ptr<C_HttpClient> T_SPC_HttpClient;	

public: // I_HttpClient
	std::string GetRequest(std::string strUrl);
 	

public:
	static T_SPC_HttpClient NewC_HttpClient(boost::asio::io_service& ioService);
	static T_SPI_HttpClient NewI_HttpClient(boost::asio::io_service& ioService);

	T_SPC_HttpClient GetSPC_HttpClient();

public:
	C_HttpClient(boost::asio::io_service& ioService);
	virtual ~C_HttpClient();

public:
	boost::asio::io_service 	m_ioService;

};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End