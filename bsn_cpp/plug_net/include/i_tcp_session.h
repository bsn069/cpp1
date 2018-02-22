#pragma once

#include <bsn_cpp/plug_net/include/i_plug_net.h>


#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>


#include <boost/function.hpp>
#include <boost/asio.hpp>

#include <stdint.h>
#include <memory>
#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_TCPSession : public std::enable_shared_from_this<I_TCPSession> {
public:
	typedef std::shared_ptr<I_TCPSession> T_SPI_TCPSession;
	typedef boost::asio::ip::tcp::socket T_Socket;
	enum E_State {
		E_State_Null, 
		E_State_Connecting, 
		E_State_Connected,
	};
	enum E_Type {
		E_Type_Null, 
		E_Type_Connect,
		E_Type_Accept,
	};

public:
	virtual I_TCPSession::T_Socket& GetSocket() = 0;

	virtual void SetState(I_TCPSession::E_State eState) = 0;
	virtual I_TCPSession::E_State GetState() const = 0;

	virtual void SetType(I_TCPSession::E_Type eType) = 0;
	virtual I_TCPSession::E_Type GetType() const = 0;

    virtual int Close() = 0;

public:
	T_SPI_TCPSession GetSPI_TCPSession() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_TCPSession() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End