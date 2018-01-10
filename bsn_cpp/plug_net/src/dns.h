#pragma once

#include <bsn_cpp/plug_net/include/i_dns.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_Dns : public I_Dns {
public:
	typedef std::shared_ptr<C_Dns> T_SPC_Dns;	

public: // I_Dns
 	virtual std::vector<std::string> Domain2IPs(std::string const& strIP) override; 
	virtual void Domain2IPs_async(std::string const& strDomain, T_DnsAsyncCB cb) override;

public:
	static T_SPC_Dns NewC_Dns(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_Dns NewI_Dns(C_PlugNet::T_SPC_PlugNet spC_PlugNet);

	T_SPC_Dns GetSPC_Dns();
	
public:
	C_Dns(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_Dns();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End