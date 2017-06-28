#include "session.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <boost/bind.hpp>
using namespace asio;
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
C_Net::C_Net()
: m_Work(m_IO)
, m_Acceptor(m_IO)
{
 
}


C_Net::~C_Net()
{
 
}
 

void C_Net::PostAccept(void)
{
	T_SharePtrCSession Session(new C_Session(m_IO));

	m_Acceptor.async_accept(
		Socket->Socket()
		, boost::bind(
			&C_Net::OnAccept
			, this
			, Session
			, placeholders::error
		)
	);
}


void C_Net::OnAccept(T_SharePtrCSession Session, const error_code& Error)
{
	if(Error)
	{
		return;
	}
	
// 	// 修改一些配置
// 	// 1
// 	{
// 		asio::ip::tcp::no_delay Option(false);
// 		Session->Socket().set_option(Option);
// 	}

// 	// 2
// 	{
// 		tcp_keepalive  In, Out;
// 		In.onoff = 1;
// 		In.keepalivetime = 1000;
// 		In.keepaliveinterval = 5000;

// 		DWORD dwBytes;     
// 		WSAIoctl(
// 			Socket->m_Socket.native(),
// 			SIO_KEEPALIVE_VALS,
// 			(LPVOID)&In,
// 			sizeof(tcp_keepalive),
// 			(LPVOID)&Out,
// 			sizeof(tcp_keepalive),
// 			&dwBytes,
// 			0,
// 			0);
// 	}

// 	// 3
// 	{
// 		socket_base::reuse_address Option(true);
// 		Socket->m_Socket.set_option(Option);
// 	}

// 	// 4
// 	{
// /*
// 		socket_base::linger Option(true, 30);
// 		Socket->m_Socket.set_option(Option);
// */
// 	}

	Session->OnAccept();
	m_Accepts.push_back(Session);
	// 发出一个Accept
	PostAccept();
}

void C_Net::Listen(std::string strIp, uint8_t uPort)
{
	if(!m_Acceptor.is_open())
	{
		m_Acceptor.open(asio::ip::tcp::v4());
	}

	{
		asio::ip::tcp::no_delay Option(false);
		m_Acceptor.set_option(Option);
	}

	{
		asio::socket_base::reuse_address Option(true);
		m_Acceptor.set_option(Option);
	}

	{
/*
		asio::socket_base::linger Option(true, 30);
		m_Acceptor.set_option(Option);
*/
	}

	{
		tcp_keepalive  In, Out;
		In.onoff = 1;
		In.keepalivetime = 1000;
		In.keepaliveinterval = 5000;

		DWORD dwBytes;     
		WSAIoctl(
			m_Acceptor.native(),
			SIO_KEEPALIVE_VALS,
			(LPVOID)&In,
			sizeof(tcp_keepalive),
			(LPVOID)&Out,
			sizeof(tcp_keepalive),
			&dwBytes,
			0,
			0
		);
	}

	auto Address = asio::ip::address_v4::from_string(strIp);
	asio::ip::tcp::endpoint EndPoint(Address, htons(uPort));

	m_Acceptor.bind(EndPoint);
	m_Acceptor.listen();

	PostAccept();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
