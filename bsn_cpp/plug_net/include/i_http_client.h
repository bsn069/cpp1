#pragma once

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_HttpClient : public std::enable_shared_from_this<I_HttpClient> {
public:
	typedef std::shared_ptr<I_HttpClient> T_SPI_HttpClient;
	
public:
 

public:
	T_SPI_HttpClient GetSPI_HttpClient() {
		D_OutInfo();
		return std::shared_from_this();
	}

public:
	virtual ~I_HttpClient() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End