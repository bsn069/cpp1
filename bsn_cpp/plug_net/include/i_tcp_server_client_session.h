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
class I_TCPServerClientSession : public std::enable_shared_from_this<I_TCPServerClientSession> {
public:
	typedef std::shared_ptr<I_TCPServerClientSession> T_SPI_TCPServerClientSession;

public:
 	virtual bool Start() = 0;
	virtual bool Stop() = 0;

public:
	T_SPI_TCPServerClientSession GetSPI_TCPServerClientSession() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_TCPServerClientSession() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End