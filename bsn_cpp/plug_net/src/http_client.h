#pragma once

#include <bsn_cpp/plug_net/include/i_http_client.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_HttpClient : public I_HttpClient {
public:
	typedef std::shared_ptr<C_HttpClient> T_SPC_HttpClient;	

public: // I_HttpClient
 	virtual std::string Get(std::string const& strDomain, std::string const& strPath) override; 
 	virtual void Get_async(std::string const& strDomain, std::string const& strPath, T_HttpClientAsyncCB cb) override; 
	// virtual void Get_async(std::string const& strUri, T_HttpClientAsyncCB cb) override;

public:
	static T_SPC_HttpClient NewC_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_HttpClient NewI_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);

	T_SPC_HttpClient GetSPC_HttpClient();
	
public:
	C_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_HttpClient();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End