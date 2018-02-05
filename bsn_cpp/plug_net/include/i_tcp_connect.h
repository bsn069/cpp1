#pragma once

#include <bsn_cpp/plug_net/include/i_address.h>
#include <bsn_cpp/plug_net/include/i_tcp_session.h>


#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>


#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <stdint.h>
#include <memory>
#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_TCPConnect : public std::enable_shared_from_this<I_TCPConnect> {
public:
	typedef std::shared_ptr<I_TCPConnect> T_SPI_TCPConnect;
	typedef boost::function<void(I_TCPSession::T_SPI_TCPSession)> T_FuncOnConnect;

public:
	virtual bool Connect(
		I_TCPSession::T_SPI_TCPSession spI_TCPSession
		, I_Address::T_SPI_Address spI_Address
		, T_FuncOnConnect func
	) = 0;
	virtual void ConnectCoro(
		boost::asio::yield_context yield
		, I_TCPSession::T_SPI_TCPSession spI_TCPSession
		, I_Address::T_SPI_Address spI_Address
		, T_FuncOnConnect func
	) = 0;
	virtual bool CanConnect(I_TCPSession::T_SPI_TCPSession spI_TCPSession) = 0;

public:
	T_SPI_TCPConnect GetSPI_TCPConnect() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_TCPConnect() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End