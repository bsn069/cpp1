#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>


D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugDataNet::C_PlugDataNet(boost::asio::io_service& ioService) 
	: m_ioService(ioService) 
	, m_Resolver(ioService) {
	D_OutInfo();
}

C_PlugDataNet::~C_PlugDataNet() {
	D_OutInfo();
}

I_PlugData* C_PlugDataNet::CreateI_PlugData(I_PlugMgr::T_SPI_PlugMgr spI_PlugMgr) {
	return New<C_PlugDataNet>(spI_PlugMgr->GetIOService());
}


void C_PlugDataNet::Domain2IPs_async_handle(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator it, std::string strIP, T_DnsAsyncCB cb) { 
	auto& vecIPs = m_Domain2IPs[strIP];
	vecIPs.clear();
	if (!ec) { 
		boost::asio::ip::tcp::resolver::iterator end;  
		for (; it != end; it++) {  
			vecIPs.push_back((*it).endpoint().address().to_string());
		}  
	} else {
		D_OutInfo1(ec);
	}

	if (cb) {
		cb(vecIPs);
	}
} 
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif