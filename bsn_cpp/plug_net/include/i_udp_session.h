#pragma once

#include <bsn_cpp/plug_net/include/i_address.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <boost/function.hpp>
#include <boost/asio.hpp>

#include <stdint.h>
#include <memory>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_UDPSession : public std::enable_shared_from_this<I_UDPSession> {
public:
	typedef std::shared_ptr<I_UDPSession>   T_SPI_UDPSession;

public:
	virtual I_Address::T_SPI_Address    GetAddress() = 0;
	virtual bool    SendTo(I_Address::T_SPI_Address spI_Address, uint8_t* pData, uint32_t u32Len) = 0;
    
public:
	T_SPI_UDPSession GetSPI_UDPSession() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_UDPSession() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End