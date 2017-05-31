#include "./main.h"
#include "./client.h"
#include "./session.h"
D_BsnNamespace1(TCP)
//////////////////////////////////////////////////////////////////////
using asio::ip::tcp;
using D_N2(Common, String)::Unicode2ANSI;

T_int32 D_const
C_Client::Connect(T_wchar D_const * D_const pwcIP, T_uint16 D_const u16Port, T_void* pUserData)
{
	tcp::endpoint endPoint;
	asio::error_code ec;
	if (T_nullptr == pwcIP)
	{
		endPoint = tcp::endpoint(tcp::v4(), u16Port);
	}
	else
	{
		string strIP;
		Unicode2ANSI(pwcIP, strIP);
		asio::ip::address_v4 addr = asio::ip::address_v4::from_string(strIP, ec);
		endPoint = tcp::endpoint(addr, u16Port);
	}
	if (ec)
	{
		cout << ec.message() << endl;
		return -999;
	}

	C_Session* pSession = New<C_Session>(m_Interface.m_IOService);
	pSession->m_State = C_Session::S_Connecting;
	C_Session::T_Ptr Session(pSession);
	pSession->SetUserData(pUserData);
	pSession->m_Socket.async_connect(
		endPoint
		, bind(&C_Client::OnConnect, this, Session, asio::placeholders::error)
		);
	return 0;
}


T_int32 D_const
C_Client::GetSessions(I_Session::T_Ptrs*& pSessions)
{
	pSessions = &(m_Sessions.Flip());
	return 0;
}



C_Client::C_Client(C_Interface& Interface)
	: m_Interface( Interface )
{

}



C_Client::~C_Client()
{

}


N_Bsn::T_void
C_Client::OnConnect(I_Session::T_Ptr D_const& Session, asio::error_code D_const& error)
{
	if (error)
	{
		cout << error.message() << endl;
		Session->Close();
		m_Sessions.WriteRef(Session);
		return;
	}
 
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
