#pragma once

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>


#include <boost/function.hpp>

#include <stdint.h>
#include <memory>
#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_HttpClient : public std::enable_shared_from_this<I_HttpClient> {
public:
	typedef std::shared_ptr<I_HttpClient> T_SPI_HttpClient;
	typedef D_N1(plug_mgr)::C_PlugDataNet::T_HttpClientAsyncCB T_HttpClientAsyncCB;

public:
 	virtual std::string Get(std::string const& strURL) = 0; 
 	virtual void Get_async(std::string const& strURL, T_HttpClientAsyncCB cb) = 0; 
 	virtual void GetCoroutine(std::string const& strURL) = 0; 

public:
	T_SPI_HttpClient GetSPI_HttpClient() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_HttpClient() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End