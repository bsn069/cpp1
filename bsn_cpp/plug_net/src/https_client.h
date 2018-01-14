#pragma once

#include <bsn_cpp/plug_net/include/i_https_client.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_HttpsClient : public I_HttpClient {
public:
	typedef std::shared_ptr<C_HttpsClient> T_SPC_HttpClient;	

public: // I_HttpClient
 	virtual std::string Get(std::string const& strURL) override; 

public:
	static T_SPC_HttpClient NewC_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_HttpClient NewI_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);

	T_SPC_HttpClient GetSPC_HttpClient();
	
public:
	C_HttpsClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_HttpsClient();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
	boost::asio::ssl::context m_ssl_context;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End