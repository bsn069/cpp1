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
class I_Address : public std::enable_shared_from_this<I_Address> {
public:
	typedef std::shared_ptr<I_Address> T_SPI_Address;

public:
  	virtual void SetAddr(std::string const& strAddr) = 0;
 	virtual void SetPort(uint16_t u16Port) = 0;
	virtual std::string const& GetAddr() = 0;
	virtual uint16_t GetPort() = 0;

public:
	T_SPI_Address GetSPI_Address() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_Address() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End