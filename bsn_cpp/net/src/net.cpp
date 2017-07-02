#include "net.h"
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
	m_bAccepting.store(false);
}


C_Net::~C_Net()
{
	
}
 
void C_Net::Run()
{
	m_IO.run();
}

void C_Net::Init()
{
	m_workThread.resize(2);
	for	(auto& pThread : m_workThread)
	{
		pThread = new std::thread(std::bind(&C_Net::Run, this));
	}	
}

void C_Net::UnInit()
{
	m_Acceptor.close();
	m_Work.~work();

	for	(auto pThread : m_workThread)
	{
		pThread->join();
		Delete(pThread);
	}
	m_workThread.clear();

	m_pLog = nullptr;
}

void C_Net::PostAccept(void)
{
	D_LogInfoFmt("p=%p", this);
	
	bool bOldValue = false;
	if (!m_bAccepting.compare_exchange_strong(bOldValue, true, std::memory_order_relaxed)) // 设置为发送中
	{
		return;
	}

	T_SharePtrCSession Session(new C_Session(m_IO));

	m_Acceptor.async_accept(
		Session->Socket()
		, boost::bind(
			&C_Net::OnAccept
			, this
			, Session
			, asio::placeholders::error
		)
	);
}


void C_Net::OnAccept(T_SharePtrCSession Session, const error_code& Error)
{
	D_LogInfoFmt("p=%p", this);
	
	if(Error)
	{
		return;
	}

	{
		asio::error_code ec;
		{
			asio::ip::tcp::no_delay Option(false);
			Session->Socket().set_option(Option, ec);
		}
		{
			asio::socket_base::keep_alive Option(true);
			Session->Socket().set_option(Option, ec);
		}
		{
			asio::socket_base::linger Option(true, 10);
			Session->Socket().set_option(Option, ec);
		}
	}

	Session->OnAccept();
	m_Accepts.push_back(Session);

	// 发出一个Accept
	m_bAccepting.store(false, std::memory_order_relaxed);
	PostAccept();
}



void C_Net::Listen(std::string strIp, uint8_t uPort)
{
	D_LogInfoFmt("p=%p", this);
	
	if(m_Acceptor.is_open())
	{
		return;
	}
	m_Acceptor.open(asio::ip::tcp::v4());

	{
		asio::ip::tcp::no_delay Option(false);
		m_Acceptor.set_option(Option);
	}

	{
		asio::socket_base::reuse_address Option(true);
		m_Acceptor.set_option(Option);
	}

	{
		asio::socket_base::linger Option(true, 30);
		m_Acceptor.set_option(Option);
	}
	
	auto Address = asio::ip::address_v4::from_string(strIp);
	asio::ip::tcp::endpoint EndPoint(Address, htons(uPort));

	m_Acceptor.bind(EndPoint);
	m_Acceptor.listen();

	PostAccept();
}

C_Net::T_SharePtrISession C_Net::Connect(std::string strIp, uint8_t uPort)
{	
	D_LogInfoFmt("p=%p", this);
	
	auto Address = asio::ip::address_v4::from_string(strIp);
	asio::ip::tcp::endpoint EndPoint(Address, htons(uPort));

	T_SharePtrCSession Session(new C_Session(m_IO));
	Session->Socket().async_connect(
		EndPoint
		, boost::bind(
			&C_Net::OnConnect
			, this
			, Session
			, asio::placeholders::error
		)
	);
	
	auto pISession = std::dynamic_pointer_cast<I_Session>(Session);
	return pISession;
}

void C_Net::OnConnect(T_SharePtrCSession Session, const error_code& Error)
{
	D_LogInfoFmt("p=%p", this);
	
	if(Error)
	{
		Session->Close();
		return;
	}

	{
		asio::error_code ec;
		{
			asio::ip::tcp::no_delay Option(false);
			Session->Socket().set_option(Option, ec);
		}
		{
			asio::socket_base::keep_alive Option(true);
			Session->Socket().set_option(Option, ec);
		}
		{
			asio::socket_base::linger Option(true, 10);
			Session->Socket().set_option(Option, ec);
		}
	}
 
	Session->OnConnect();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
