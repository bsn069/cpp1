#include "./main.h"
#include "./server.h"
D_BsnNamespace1(TCP)
//////////////////////////////////////////////////////////////////////

using asio::ip::tcp;
using D_N2(Common, String)::Unicode2ANSI;


T_int32 D_const
C_Server::Bind(T_wchar D_const * D_const pwcIP, T_uint16 D_const u16Port)
{
	if (IsBind())
	{
		return -4;
	}

	asio::error_code ec;
	if (T_nullptr == pwcIP)
	{
		m_pEndPoint = New<tcp::endpoint>(tcp::v4(), u16Port);
	}
	else
	{
		string strIP;
		Unicode2ANSI(pwcIP, strIP);
		asio::ip::address_v4 addr = asio::ip::address_v4::from_string(strIP, ec);

		m_pEndPoint = New<tcp::endpoint>(addr, u16Port);
	}
	if (ec)
	{
		cout << ec.message() << endl;
		return -999;
	}
	return 0;

}


T_int32 D_const
C_Server::Listen()
{
	if (IsListen())
	{
		return -6;
	}
	if (!IsBind())
	{
		return -5;
	}

	m_Accepter.open(asio::ip::tcp::v4());
	m_Accepter.set_option(asio::ip::tcp::acceptor::reuse_address(true));
	asio::error_code ec;
	m_Accepter.bind(*m_pEndPoint, ec);
	if (ec)
	{
		m_Accepter.close();
		return -999;
	}
	m_Accepter.listen();
	Accept();

	return 0;
}


T_int32 D_const
C_Server::StopListen()
{
	if (!IsListen())
	{
		return -7;
	}
	m_Accepter.close();
	return 0;
}


T_int32 D_const
C_Server::GetSessions(I_Session::T_Ptrs*& pSessions)
{
	pSessions = &(m_Sessions.Flip());
	return 0;
}



C_Server::C_Server(C_Interface& Interface, asio::io_service& IOService)
	: m_Interface( Interface )
	, m_Accepter( IOService )
	, m_pEndPoint( T_nullptr )
{

}


T_int32 D_const
C_Server::Stop()
{
	Delete(m_pEndPoint);
	return 0;
}


N_Bsn::T_void
C_Server::Accept()
{
	C_Session* pSession = New<C_Session>(m_Interface.m_IOService);
	pSession->m_State = C_Session::S_Accepting;
	C_Session::T_Ptr Session(pSession);
	m_Accepter.async_accept(
		pSession->m_Socket
		, bind(
			&C_Server::OnAccept
			, this
			, Session
			, asio::placeholders::error
			)
		);
}


N_Bsn::T_void
C_Server::OnAccept(I_Session::T_Ptr D_const& Session, asio::error_code D_const& error)
{
	if (error)
	{
		cout << error.message() << endl;
		Session->Close();
		return;
	}
	Accept();

	C_Session* pSession = static_cast<C_Session*>(Session.get());
	{
		asio::error_code ec;
		{
			asio::ip::tcp::no_delay Option(false);
			pSession->m_Socket.set_option(Option, ec);
		}
		{
			asio::socket_base::keep_alive Option(true);
			pSession->m_Socket.set_option(Option, ec);
		}
		{
			asio::socket_base::linger Option(true, 10);
			pSession->m_Socket.set_option(Option, ec);
		}
	}
	D_N2(Common, String)::ANSI2Unicode(
		pSession->m_Socket.remote_endpoint().address().to_v4().to_string().c_str()
		, pSession->m_wstrRemoteIP
		);
	pSession->m_u16RemotePort = pSession->m_Socket.remote_endpoint().port();
	pSession->m_State = C_Session::S_Established;
	pSession->PostRead();
	m_Sessions.WriteRef(Session);
}

D_BsnNamespace1End
