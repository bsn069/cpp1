#pragma once

#include <bsn_cpp/plug_net/include/i_address.h>


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
class I_TCPServer : public std::enable_shared_from_this<I_TCPServer> {
public:
	typedef std::shared_ptr<I_TCPServer> T_SPI_TCPServer;

public:
	virtual I_Address::T_SPI_Address GetAddress() = 0;
	virtual bool SetAddress(I_Address::T_SPI_Address spI_Address) = 0;

	virtual bool Start() = 0;
	virtual bool Stop() = 0;

	virtual bool StartListen() = 0;
	virtual bool StopListen() = 0;
	
	virtual bool StopAllClient() = 0;

public:
	T_SPI_TCPServer GetSPI_TCPServer() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_TCPServer() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End