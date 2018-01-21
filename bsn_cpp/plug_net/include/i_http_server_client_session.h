#pragma once

// #include <bsn_cpp/plug_net/include/i_address.h>


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
class I_HttpServerClientSession : public std::enable_shared_from_this<I_HttpServerClientSession> {
public:
	typedef std::shared_ptr<I_HttpServerClientSession> T_SPI_HttpServerClientSession;

public:


public:
	T_SPI_HttpServerClientSession GetSPI_HttpServerClientSession() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_HttpServerClientSession() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End