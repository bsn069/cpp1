#pragma once

class FBNETWORK_API CFBNetwork_A
{
public:
	io_service													m_IO;
	io_service::work											m_Work;
	ip::tcp::acceptor											m_Acceptor;

	CFBKernel_Vector<HANDLE>									m_Threads;

	CFBKernel_Double<CFBNetwork_A_Socket::Ptr>					m_Accepts;						// 新接受的连接

public:
	void									Accept(void);

	void									OnAccept(CFBNetwork_A_Socket::Ptr Socket, const error_code& Error);
	void									OnConnect(CFBNetwork_A_Socket::Ptr Socket, const error_code& Error);

public:
											CFBNetwork_A();
	virtual									~CFBNetwork_A();

	BOOL									Init(int nIOCPThreads, DWORD dwThreads);
	void									Quit(void);

	void									Listen(sockaddr_in* pAddr);
	void									Stop(void);

	CFBNetwork_A_Socket::Ptr				Connect(sockaddr_in* pAddr);
	void									Close(CFBNetwork_A_Socket::Ptr Socket);
};
