#include "net.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <boost/bind.hpp>

D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
C_Net::C_Net(asio::io_service& io)
	: m_IO(io)
	, m_spI_Common(nullptr)
	, m_spI_Log(nullptr)
{
 
}


C_Net::~C_Net() {
	m_spI_Common 	= nullptr;
	m_spI_Log		= nullptr;
}
 
bool
C_Net::Connect(
	std::string const& strIp
	, uint16_t u16Port
	, T_FuncOnConnect func
) {	
	auto Address = asio::ip::address_v4::from_string(strIp);
	asio::ip::tcp::endpoint EndPoint(Address, htons(u16Port));

	auto p = new C_Session(m_IO);
	auto spC_Session = C_Session::T_SPC_Session(p);
	spC_Session->GetSocket().async_connect(
		EndPoint
		, boost::bind(
			&C_Net::OnConnect
			, this
			, spC_Session
			, asio::placeholders::error
			, func
		)
	);

	return true;
}

void 
C_Net::OnConnect(
	C_Session::T_SPC_Session 	spC_Session
	, const error_code& 		errorCode
	, T_FuncOnConnect 			func
) {
	if (errorCode) {
		spC_Session->Close();
		func(nullptr);
		return;
	}

	{
		asio::error_code ec;
		{
			asio::ip::tcp::no_delay Option(false);
			spC_Session->GetSocket().set_option(Option, ec);
		}
		{
			asio::socket_base::keep_alive Option(true);
			spC_Session->GetSocket().set_option(Option, ec);
		}
		{
			asio::socket_base::linger Option(true, 10);
			spC_Session->GetSocket().set_option(Option, ec);
		}
	}
 
 	auto spI_Session = std::dynamic_pointer_cast<I_Session>(spC_Session);
	func(spI_Session);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
