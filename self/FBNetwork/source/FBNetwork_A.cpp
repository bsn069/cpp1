#include "../include/FBNetwork_Port.h"

DWORD FBNetwork_A_WorkerThread(LPVOID pParam)
{
	CFBNetwork_A* pA = (CFBNetwork_A*)pParam;
	pA->m_IO.run();
	return 0;
}

void CFBNetwork_A::Accept(void)
{
	CFBNetwork_A_Socket::Ptr Socket(new CFBNetwork_A_Socket(this));
	InterlockedExchange((LONG volatile*)&Socket->m_State, CFBNetwork_A_Socket::S_WATTINGORCONNECTING);

	m_Acceptor.async_accept(
		Socket->m_Socket,
		bind(&CFBNetwork_A::OnAccept, this, Socket, placeholders::error));
}

void CFBNetwork_A::OnAccept(CFBNetwork_A_Socket::Ptr Socket, const error_code& Error)
{
	if(Error)
	{
		return;
	}
	
	//
	Socket->m_Local = Socket->m_Socket.local_endpoint().address();
	Socket->m_Remote = Socket->m_Socket.remote_endpoint().address();

	// 修改一些配置
	// 1
	{
		ip::tcp::no_delay Option(false);
		Socket->m_Socket.set_option(Option);
	}

	// 2
	{
		tcp_keepalive  In, Out;
		In.onoff = 1;
		In.keepalivetime = 1000;
		In.keepaliveinterval = 5000;

		DWORD dwBytes;     
		WSAIoctl(
			Socket->m_Socket.native(),
			SIO_KEEPALIVE_VALS,
			(LPVOID)&In,
			sizeof(tcp_keepalive),
			(LPVOID)&Out,
			sizeof(tcp_keepalive),
			&dwBytes,
			0,
			0);
	}

	// 3
	{
		socket_base::reuse_address Option(true);
		Socket->m_Socket.set_option(Option);
	}

	// 4
	{
/*
		socket_base::linger Option(true, 30);
		Socket->m_Socket.set_option(Option);
*/
	}

	// 发出一个异步读取
	Socket->Read();

	// 通知上层
	InterlockedExchange((LONG volatile*)&Socket->m_State, CFBNetwork_A_Socket::S_ESTABLISHED);
	m_Accepts.Push(Socket);

	// 发出一个Accept
	Accept();
}
void CFBNetwork_A::OnConnect(CFBNetwork_A_Socket::Ptr Socket, const error_code& Error)
{
	if(Error)
	{
		InterlockedExchange((LONG volatile*)&Socket->m_State, CFBNetwork_A_Socket::S_CLOSE);
		return;
	}

	//
	Socket->m_Local = Socket->m_Socket.local_endpoint().address();
	Socket->m_Remote = Socket->m_Socket.remote_endpoint().address();

	// 修改一些配置
	// 1
	{
		ip::tcp::no_delay Option(false);
		Socket->m_Socket.set_option(Option);
	}

	// 2
	{
		tcp_keepalive  In, Out;
		In.onoff = 1;
		In.keepalivetime = 1000;
		In.keepaliveinterval = 5000;

		DWORD dwBytes;     
		WSAIoctl(
			Socket->m_Socket.native(),
			SIO_KEEPALIVE_VALS,
			(LPVOID)&In,
			sizeof(tcp_keepalive),
			(LPVOID)&Out,
			sizeof(tcp_keepalive),
			&dwBytes,
			0,
			0);
	}

	// 3
	{
		socket_base::reuse_address Option(true);
		Socket->m_Socket.set_option(Option);
	}

	// 4
	{
/*
		socket_base::linger Option(true, 30);
		Socket->m_Socket.set_option(Option);
*/
	}

	// 发出一个异步读取
	Socket->Read();

	// 通知上层
	InterlockedExchange((LONG volatile*)&Socket->m_State, CFBNetwork_A_Socket::S_ESTABLISHED);
}

CFBNetwork_A::CFBNetwork_A() : m_Work(m_IO), m_Acceptor(m_IO)
{
}
CFBNetwork_A::~CFBNetwork_A()
{
	Quit();
}

BOOL CFBNetwork_A::Init(int nIOCPThreads, DWORD dwThreads)
{
	// 创建工作者线程
	DWORD dwThreadID;
	for(DWORD n = 0; n < dwThreads; n++)
	{
		m_Threads() = CreateThread(
			0,
			0, 
			(LPTHREAD_START_ROUTINE)FBNetwork_A_WorkerThread,
			this,
			0,
			&dwThreadID);

		if(!m_Threads[n])
		{
			return false;
		}
	}
	return true;
}
void CFBNetwork_A::Quit(void)
{
	Stop();

	// bug这里先临时这么写，可能是调用stop或者reset，但是没找到资料
	// 这么先替代应该是没问题的
	m_Work.~work();

	// 等待所有工作线程退出
	WaitForMultipleObjects(m_Threads.Size(), m_Threads.Ptr(), TRUE, INFINITE);
}

void CFBNetwork_A::Listen(sockaddr_in* pAddr)
{
	if(!m_Acceptor.is_open())
	{
		m_Acceptor.open(ip::tcp::v4());
	}

	// 修改一些配置
	// 1
	{
		ip::tcp::no_delay Option(false);
		m_Acceptor.set_option(Option);
	}

	// 2
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
			0);
	}

	// 3
	{
		socket_base::reuse_address Option(true);
		m_Acceptor.set_option(Option);
	}

	// 4
	{
/*
		socket_base::linger Option(true, 30);
		m_Acceptor.set_option(Option);
*/
	}

	ip::address_v4 Address(htonl(pAddr->sin_addr.S_un.S_addr));
	ip::tcp::endpoint EndPoint(Address, htons(pAddr->sin_port));

	m_Acceptor.bind(EndPoint);
	m_Acceptor.listen();

	// 发出一个Accept
	Accept();
}
void CFBNetwork_A::Stop(void)
{
	m_Acceptor.close();
}

CFBNetwork_A_Socket::Ptr CFBNetwork_A::Connect(sockaddr_in* pAddr)
{
	ip::address_v4 Address(htonl(pAddr->sin_addr.S_un.S_addr));
	ip::tcp::endpoint EndPoint(Address, htons(pAddr->sin_port));

	CFBNetwork_A_Socket::Ptr NewSocket(new CFBNetwork_A_Socket(this));
	InterlockedExchange((LONG volatile*)&NewSocket->m_State, CFBNetwork_A_Socket::S_WATTINGORCONNECTING);

	NewSocket->m_Socket.async_connect(
		EndPoint,
		bind(&CFBNetwork_A::OnConnect, this, NewSocket, placeholders::error));

	return NewSocket;
}
void CFBNetwork_A::Close(CFBNetwork_A_Socket::Ptr Socket)
{
	if(Socket.get())
	{
		Socket->m_Socket.close();
	}
}
