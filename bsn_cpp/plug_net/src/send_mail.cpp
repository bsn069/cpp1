#include <bsn_cpp/plug_net/src/send_mail.h>
#include <bsn_cpp/plug_net/src/dns.h>
#include <bsn_cpp/plug_net/src/url.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_SendMail::C_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet) {
	D_OutInfo();
}

C_SendMail::~C_SendMail() {
	D_OutInfo();
 
}

C_SendMail::T_SPC_SendMail C_SendMail::GetSPC_SendMail() {
	D_OutInfo();
	auto spI_SendMail = GetSPI_SendMail();
	auto spC_SendMail = std::dynamic_pointer_cast<C_SendMail>(spI_SendMail);
	return spC_SendMail;
}

void C_SendMail::SpawnCoroutine() {
    boost::asio::spawn(m_spC_PlugNet->GetIOService(),
        boost::bind(&C_SendMail::CoroutineImp,
          GetSPC_SendMail(), _1));
}

void C_SendMail::CoroutineImp(boost::asio::yield_context yield) {
	boost::system::error_code ec; 
 
}
 
void C_SendMail::SendTest() {
    boost::asio::spawn(m_spC_PlugNet->GetIOService(),
        boost::bind(&C_SendMail::SendTestCoroutineImp,
          GetSPC_SendMail(), _1));
}

void C_SendMail::SendTestCoroutineImp(boost::asio::yield_context yield) {
	boost::system::error_code ec; 

	boost::asio::ip::tcp::resolver::query qry("smtp.qq.com", "25");
	boost::asio::ip::tcp::resolver 	rsv(m_spC_PlugNet->GetIOService());
	auto endpoint_iterator = rsv.async_resolve(qry, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 

	auto Socket = boost::asio::ip::tcp::socket(m_spC_PlugNet->GetIOService());
	boost::asio::async_connect(Socket, endpoint_iterator, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 

	boost::asio::streambuf request;  
	std::ostream request_stream(&request);  
	request_stream << "GET " << spC_URL->GetPath() << " HTTP/1.1\r\n";  
	request_stream << "Host: " << spC_URL->GetHost() << "\r\n";  
	request_stream << "Accept: */*\r\n";  
	request_stream << "Connection: close\r\n\r\n"; 

	boost::asio::async_write(Socket, request, boost::asio::transfer_all(), yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 

	// boost::asio::streambuf response;  
	// boost::asio::async_read(
	// 	Socket
	// 	, response
	// 	, boost::asio::transfer_all()
	// 	, yield[ec]
	// );
	// if (ec && ec != boost::asio::error::eof) {  
	// 	D_OutInfo1(boost::system::system_error(ec).what());   
	// 	return;
	// } 

	// std::istream is(&response);  
	// is.unsetf(std::ios_base::skipws);  
	// std::string sz;  
	// sz.append(std::istream_iterator<char>(is), std::istream_iterator<char>());  
	// D_OutInfo1(sz);
}
//////////////////////////////////////////////////////////////////////
C_SendMail* CreateC_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_SendMail* pC_SendMail = New<C_SendMail>(spC_PlugNet);
	return pC_SendMail;
}

void ReleaseC_SendMail(I_SendMail* pI_SendMail) {
	D_OutInfo();
	C_SendMail* pC_SendMail = static_cast<C_SendMail*>(pI_SendMail);
	Delete(pC_SendMail);
}

C_SendMail::T_SPC_SendMail C_SendMail::NewC_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_SendMail = CreateC_SendMail(spC_PlugNet);
	auto spC_SendMail = C_SendMail::T_SPC_SendMail(pC_SendMail, ReleaseC_SendMail);
	return spC_SendMail;
}

C_SendMail::T_SPI_SendMail C_SendMail::NewI_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_SendMail = C_SendMail::NewC_SendMail(spC_PlugNet);
	auto spI_SendMail = spC_SendMail->GetSPI_SendMail();
	return spI_SendMail;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif