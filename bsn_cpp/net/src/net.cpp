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
 
D_FunImp I_Buffer* 
CreateCSession(asio::io_service& io, D_N1(common)::T_SPI_Common spI_Common) {
	C_Session* imp = New<C_Session>(io, spI_Common);
	return imp;
}

D_FunImp void 
ReleaseCSession(I_Session* iSession) {
	C_Session* pImp = static_cast<C_Session*>(iSession);
	Delete(pImp);
}

bool
C_Net::Connect(
	std::string const& strIp
	, uint16_t u16Port
	, T_FuncOnConnect func
) {	
	auto Address = asio::ip::address_v4::from_string(strIp);
	asio::ip::tcp::endpoint EndPoint(Address, htons(u16Port));

	auto spI_Session = C_Session::T_SPC_Session(
		CreateCSession(m_IO, m_spI_Common)
		, ReleaseCSession
	);
 	auto spC_Session = std::dynamic_pointer_cast<C_Session>(spI_Session);
	spC_Session->GetSocket().async_connect(
		EndPoint
		, boost::bind(
			&C_Net::OnConnect
			, this
			, spI_Session
			, asio::placeholders::error
			, func
		)
	);

	return true;
}

void 
C_Net::OnConnect(
	C_Session::T_SPI_Session 	spI_Session
	, const error_code& 		errorCode
	, T_FuncOnConnect 			func
) {
	if (errorCode) {
		spI_Session->Close();
		func(nullptr);
		return;
	}

	{
		auto spC_Session = std::dynamic_pointer_cast<C_Session>(spI_Session);
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
 
	func(spI_Session);
}

void	
C_Net::WaitQuit() {
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
