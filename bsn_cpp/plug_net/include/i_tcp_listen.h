#pragma once

#include <bsn_cpp/plug_net/include/i_address.h>
#include <bsn_cpp/plug_net/include/i_tcp_session.h>


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
class I_TCPListen : public std::enable_shared_from_this<I_TCPListen> {
public:
	typedef std::shared_ptr<I_TCPListen> T_SPI_TCPListen;
	typedef boost::function<I_TCPSession::T_SPI_TCPSession()> T_FuncNew;
	typedef boost::function<void(I_TCPSession::T_SPI_TCPSession)> T_FuncOnAccept;

public:
	virtual I_Address::T_SPI_Address GetAddress() = 0;
	virtual bool SetAddress(I_Address::T_SPI_Address spI_Address) = 0;

	virtual bool StartListen() = 0;
	virtual bool StopListen() = 0;
    virtual bool InListen() = 0;

	virtual void SetFuncNew(T_FuncNew func) = 0;
	virtual void SetFuncOnAccept(T_FuncOnAccept func) = 0;

public:
	T_SPI_TCPListen GetSPI_TCPListen() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_TCPListen() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End