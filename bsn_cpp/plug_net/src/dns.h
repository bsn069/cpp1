#pragma once

#include <bsn_cpp/plug_net/include/i_dns.h>

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

public:
	static T_SPC_Dns NewC_Dns(boost::asio::io_service& ioService);
	static T_SPI_Dns NewI_Dns(boost::asio::io_service& ioService);

	T_SPC_Dns GetSPC_Dns();

public:
	C_Dns(boost::asio::io_service& ioService);
	virtual ~C_Dns();

public:
	boost::asio::io_service& 	m_ioService;
	boost::asio::ip::tcp::resolver m_Resolver;

};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End