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
class I_HttpsClient : public std::enable_shared_from_this<I_HttpsClient> {
public:
	typedef std::shared_ptr<I_HttpsClient> T_SPI_HttpsClient;

public:
 	virtual std::string Get(std::string const& strURL) = 0; 

public:
	T_SPI_HttpsClient GetSPI_HttpsClient() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_HttpsClient() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End