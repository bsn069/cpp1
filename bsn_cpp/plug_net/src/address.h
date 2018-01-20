#pragma once

#include <bsn_cpp/plug_net/include/i_address.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_Address : public I_Address {
public:
	typedef std::shared_ptr<C_Address> T_SPC_Address;	

public: // I_Address
	virtual void SetAddr(std::string const& strAddr) override;
 	virtual void SetPort(uint16_t u16Port) override;
	virtual std::string const& GetAddr() override;
	virtual uint16_t GetPort() override;

public:
	static T_SPC_Address NewC_Address();
	static T_SPI_Address NewI_Address();

	T_SPC_Address GetSPC_Address();

public:
	C_Address();
	virtual ~C_Address();

public:
	std::string m_strAddr;
	uint16_t 	m_u16Port;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End