#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>
#include <bsn_cpp/plug_net/include/i_dns.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_TCPListen;
class I_TCPConnect;
class I_Address;

class I_PlugNet : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugNet> 		T_SPI_PlugNet;
	typedef std::shared_ptr<I_TCPListen> 	T_SPI_TCPListen;
	typedef std::shared_ptr<I_TCPConnect> 	T_SPI_TCPConnect;
	typedef std::shared_ptr<I_Address> 		T_SPI_Address;

public:
 	virtual I_Dns::T_SPI_Dns 	NewI_Dns() = 0;
 	virtual T_SPI_TCPListen 	NewI_TCPListen() = 0;
 	virtual T_SPI_TCPConnect 	NewI_TCPConnect() = 0;
 	virtual T_SPI_Address 		NewI_Address() = 0;
 

public:
	T_SPI_PlugNet GetSPI_PlugNet() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugNet = std::dynamic_pointer_cast<I_PlugNet>(spI_Plug);
		return spI_PlugNet;
	}

public:
	virtual ~I_PlugNet() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End