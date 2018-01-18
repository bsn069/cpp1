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
class C_HttpsClient : public I_HttpsClient {
public:
	typedef std::shared_ptr<C_HttpsClient> T_SPC_HttpsClient;	
	typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> T_Socket;

public: // I_HttpsClient
 	virtual std::string Get(std::string const& strURL) override; 

public:
	static T_SPC_HttpsClient NewC_HttpsClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_HttpsClient NewI_HttpsClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);

	T_SPC_HttpsClient GetSPC_HttpsClient();
	
	bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx);

public:
	C_HttpsClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_HttpsClient();

public:
	boost::asio::ssl::context m_ssl_context;
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End