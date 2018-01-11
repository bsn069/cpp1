#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug_data.h>
#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>

#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/function.hpp>

#include <stdint.h>
#include <memory>
#include <set>
#include <vector>
#include <string>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugDataNet : public I_PlugData {
public:
	typedef std::vector<std::string> 		T_IPs;
	typedef std::map<std::string, T_IPs> 	T_Domain2IPs; 
	typedef boost::function<void(T_IPs)> 	T_DnsAsyncCB;
	typedef boost::function<void(T_IPs)> 	T_HttpClientAsyncCB;

public:
	boost::asio::io_service& 		m_ioService;
	boost::asio::ip::tcp::resolver 	m_Resolver;
	T_Domain2IPs					m_Domain2IPs;

public:
	void Domain2IPs_async_handle(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator it, std::string strIP, T_DnsAsyncCB cb);

public:
	C_PlugDataNet(boost::asio::io_service& ioService);
	virtual ~C_PlugDataNet();

	static I_PlugData* CreateI_PlugData(I_PlugMgr::T_SPI_PlugMgr);
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End