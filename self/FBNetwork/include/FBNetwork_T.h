#pragma once

// 这个类不是线程安全的（目前不需要）
class FBNETWORK_API CFBNetwork_T
{
public:
	HANDLE														m_hIOCP;

	LPFN_GETACCEPTEXSOCKADDRS									m_pGetAcceptExSocketaddrs;
	LPFN_CONNECTEX												m_pConnectEx;

	CFBKernel_Vector<HANDLE>									m_Threads;

	DWORD volatile												m_dwSockets;

public:
	CFBNetwork_T_Socket*					NewSocket(void);

public:
											CFBNetwork_T();
	virtual									~CFBNetwork_T();

	BOOL									Init(int nIOCPThreads, DWORD dwThreads);
	void									Quit(void);

	CFBNetwork_T_Socket*					Listen(sockaddr_in* pAddr);
	CFBNetwork_T_Socket*					Connect(sockaddr_in* pAddr);
	void									Close(CFBNetwork_T_Socket** pSocket, BOOL bForce = true);
};
