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
class I_Dns : public std::enable_shared_from_this<I_Dns> {
public:
	typedef std::shared_ptr<I_Dns> T_SPI_Dns;
	typedef D_N1(plug_mgr)::C_PlugDataNet::T_DnsAsyncCB T_DnsAsyncCB;

public:
	virtual std::vector<std::string> Domain2IPs(std::string const& strIP) = 0;
	virtual void Domain2IPs_async(std::string const& strDomain, T_DnsAsyncCB cb) = 0;

public:
	T_SPI_Dns GetSPI_Dns() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_Dns() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End