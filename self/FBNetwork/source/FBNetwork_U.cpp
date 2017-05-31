#include "../include/FBNetwork_Port.h"

DWORD CFBNetwork_U::Thread(CFBNetwork_U* pU)
{
	return pU->Thread_Process();
}

DWORD CFBNetwork_U::Thread_Process(void)
{
	CFBKernel_FPS FPS;
	FPS.SetDelay(1.0 / 5.0);

	while(1)
	{
		double dElapsed = FPS.Delay();

		if(m_bQuit)
		{
			break;
		}

		CFBNetwork_U_Socket* pSocket = 0;
		while(pSocket = GetSocket(pSocket))
		{
			switch(pSocket->m_State)
			{
			case CFBNetwork_U_Socket::S_CLOSE:
				{
					CFBNetwork_U_Socket* pPrevSocket = PopSocket(pSocket);
					m_DSockets.Push_Back(pSocket);

					pSocket = pPrevSocket;
				}
				break;
			case CFBNetwork_U_Socket::S_CONNECTING:
				{
					pSocket->OnTimer_Connecting(dElapsed);
				}
				break;
			case CFBNetwork_U_Socket::S_ESTABLISHED:
				{
					pSocket->OnTimer_Established(dElapsed);
				}
				break;
			}
		}

		CFBNetwork_U_Socket* pNextSocket = 0;
		pSocket = m_DSockets.GetHead();
		while(pSocket)
		{
			pNextSocket = m_DSockets.GetNext(pSocket);

			if(
				!pSocket->m_OSNotify.List() && 
				!pSocket->m_bUsedByIS &&
				pSocket->m_bDiscarded)
			{
				m_DSockets.Pop(pSocket);
				FB_DELETE(pSocket);
			}
			pSocket = pNextSocket;
		}
	}
	return 0;
}

void CFBNetwork_U::PushSocket(CFBNetwork_U_Socket* pSocket)
{
	__int64 nAddr;

	switch(IDType(pSocket->m_dwID))
	{
	case IDT_P2P:
		{
			nAddr = 0;
		}
		break;
	case IDT_CS:
		{
			nAddr = CFBNetwork::Addr2Int64(&pSocket->m_RAddr);
		}
		break;
	}

	lock_guard<shared_mutex> Guard(m_SocketMutex);

	m_Sockets.Push_Back(pSocket);

	IDMap* pIDMap = m_AddrMap[nAddr];
	if(!pIDMap)
	{
		pIDMap = FB_NEW(IDMap, 1);
		m_AddrMap[nAddr] = pIDMap;
	}
	(*pIDMap)[pSocket->m_dwID] = pSocket;
}
CFBNetwork_U_Socket* CFBNetwork_U::PopSocket(CFBNetwork_U_Socket* pSocket)
{
	__int64 nAddr;

	switch(IDType(pSocket->m_dwID))
	{
	case IDT_CS:
		{
			nAddr = CFBNetwork::Addr2Int64(&pSocket->m_RAddr);
		}
		break;
	case IDT_P2P:
		{
			nAddr = 0;
		}
		break;
	}

	lock_guard<shared_mutex> Guard(m_SocketMutex);

	IDMap* pIDMap = m_AddrMap[nAddr];
	pIDMap->erase(pSocket->m_dwID);
	if(pIDMap->size() == 0)
	{
		m_AddrMap.erase(nAddr);
		FB_DELETE(pIDMap);
	}

	CFBNetwork_U_Socket* pPrevSocket = m_Sockets.GetPrev(pSocket);
	m_Sockets.Pop(pSocket);

	return pPrevSocket;
}
CFBNetwork_U_Socket* CFBNetwork_U::QuerySocket(sockaddr_in* pAddr, DWORD dwID, BOOL bUsedByIS)
{
	__int64 nAddr;

	switch(IDType(dwID))
	{
	case IDT_CS:
		{
			nAddr = CFBNetwork::Addr2Int64(pAddr);
		}
		break;
	case IDT_P2P:
		{
			nAddr = 0;
		}
		break;
	}

	shared_lock<shared_mutex> Guard(m_SocketMutex);

	AddrMap::iterator AddrIt = m_AddrMap.find(nAddr);
	if(AddrIt != m_AddrMap.end())
	{
		IDMap::iterator IDIt = AddrIt->second->find(dwID);
		if(IDIt != AddrIt->second->end())
		{
			CFBNetwork_U_Socket* pSocket = IDIt->second;

			if(IDType(dwID) == IDT_P2P)
			{
				CopyMemory(&pSocket->m_RAddr, pAddr, sizeof(sockaddr_in));
			}
			if(bUsedByIS)
			{
				pSocket->SetUsedByIS(true);
			}
			return pSocket;
		}
	}
	return 0;
}
CFBNetwork_U_Socket* CFBNetwork_U::GetSocket(CFBNetwork_U_Socket* pSocket)
{
	shared_lock<shared_mutex> Guard(m_SocketMutex);

	if(!pSocket)
	{
		return m_Sockets.GetHead();
	}
	return m_Sockets.GetNext(pSocket);
}

DWORD CFBNetwork_U::ID(sockaddr_in* pAddr)
{
	__int64 nID;
	DWORD dwID;

	while(1)
	{
		do
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&nID);
		}
		while(nID == 0);

		dwID = (DWORD)nID;
		dwID |= 0x80000000;

		if(!QuerySocket(pAddr, dwID, false))
		{
			break;
		}
	}
	return dwID;
}
CFBNetwork_U::IDTYPE CFBNetwork_U::IDType(DWORD dwID)
{
	if((dwID & 0x80000000) == 0x80000000)
	{
		return IDT_CS;
	}
	return IDT_P2P;
}

DWORD CFBNetwork_U::SwapID(DWORD dwID)
{
	return dwID ^ 0x40000000;
}

CFBNetwork_U::CFBNetwork_U()
{
	m_bQuit = true;
}
CFBNetwork_U::~CFBNetwork_U()
{
	Quit();
}

BOOL CFBNetwork_U::Init(sockaddr_in* pAddr)
{
	InterlockedExchange((LONG volatile*)&m_bListen, false);

	InterlockedExchange((LONG volatile*)&m_bQuit, false);

	DWORD dwThreadID;
	m_hThread = CreateThread(
		0,
		0, 
		(LPTHREAD_START_ROUTINE)Thread,
		this,
		0,
		&dwThreadID);

	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	if(::bind(m_Socket, (sockaddr*)pAddr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		return false;
	}

	DWORD dwMS = 1000;
	if(setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&dwMS, sizeof(DWORD)) == SOCKET_ERROR)
	{
		return false;
	}

	int nBufferSize = (DWORD)(-1);
	if(setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&nBufferSize, sizeof(int)) == SOCKET_ERROR)
	{
		return false;
	}

	nBufferSize = (DWORD)(-1);
	if(setsockopt(m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&nBufferSize, sizeof(int)) == SOCKET_ERROR)
	{
		return false;
	}

	m_IS.Init(this);
	m_OS.Init(this);

	return true;
}
void CFBNetwork_U::Quit(void)
{
	if(m_bQuit)
	{
		return;
	}

	m_IS.Quit();
	m_OS.Quit();

	InterlockedExchange((volatile LONG*)&m_bQuit, true);

	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);

	CFBNetwork_U_Socket* pSocket;
	while(pSocket = m_Sockets.GetHead())
	{
		PopSocket(pSocket);

		Close(pSocket);
		FB_DELETE(pSocket);
	}
	while(pSocket = m_DSockets.GetHead())
	{
		m_DSockets.Pop(pSocket);

		Close(pSocket);
		FB_DELETE(pSocket);
	}

	shutdown(m_Socket, SD_BOTH);
	closesocket(m_Socket);
}

void CFBNetwork_U::Listen(BOOL bTrue)
{
	InterlockedExchange((LONG volatile*)&m_bListen, bTrue);
}
CFBKernel_Vector<CFBNetwork_U_Socket*>* CFBNetwork_U::Accepts(void)
{
	return m_Accepts.Flip();
}

CFBNetwork_U_Socket* CFBNetwork_U::Connect(sockaddr_in* pAddr, char* pData, DWORD dwDatas, DWORD dwID, BOOL bBlock)
{
	// 附加数据长度校验
	if(CFBNetwork_U_Dg::HEADERSIZE + dwDatas > CFBNetwork_U_Dg::TOTALSIZE)
	{
		return 0;
	}

	// 如果指定ID那么ID类型必须是P2P
	if(dwID && IDType(dwID) != IDT_P2P)
	{
		return 0;
	}

	// 如果是ID是P2P类型那么就要看看指定ID的连接是否已经存在了
	// （出现重复的情况是因为用户可能在同一进程发起同一ID的连接，这个ID是协助服务器传递过来的，或者传递的ID重复了）
	/*CFBNetwork_U_Socket* pSocket = QuerySocket(pAddr, dwID, false);
	if(pSocket)
	{
		return 0;
	}*/

	CFBNetwork_U_Socket* pSocket = FB_NEW(CFBNetwork_U_Socket, 1);
	pSocket->Init(pAddr, dwID, this);
	PushSocket(pSocket);

	if(dwDatas)
	{
		pSocket->m_dwLDatas = dwDatas;
		pSocket->m_LData.Resize(pSocket->m_dwLDatas);
		CopyMemory(&pSocket->m_LData[0], pData, pSocket->m_dwLDatas);
	}

	if(bBlock)
	{
		pSocket->m_hConnectEvent = CreateEvent(0, false, false, 0);
	}
	else
	{
		pSocket->m_hConnectEvent = 0;
	}

	// 发送连接消息
	CFBNetwork_U_Dg Dg;
	Dg.SetFlagWnd(CFBNetwork_U_Dg::OPEN, pSocket->m_dwRBuffer);
	if(pSocket->m_dwLDatas)
	{
		Dg.m_dwLen += pSocket->m_dwLDatas;
		CopyMemory(Dg.m_Content.m_pData, &pSocket->m_LData[0], pSocket->m_dwLDatas);
	}

	pSocket->SendTo(&Dg);

	// 是否阻塞等待
	if(bBlock)
	{
		WaitForSingleObject(pSocket->m_hConnectEvent, INFINITE);
		CloseHandle(pSocket->m_hConnectEvent);
		pSocket->m_hConnectEvent = 0;
	}
	return pSocket;
}
void CFBNetwork_U::Close(CFBNetwork_U_Socket* pSocket)
{
	if(!pSocket || pSocket->m_bDiscarded)
	{
		return;
	}
	
	// 发送断开消息
	CFBNetwork_U_Dg Dg;
	Dg.SetFlagWnd(CFBNetwork_U_Dg::CLOSE, 0);

	pSocket->SendTo(&Dg);

	pSocket->SetState(CFBNetwork_U_Socket::S_CLOSE);

	InterlockedExchange((LONG volatile*)&pSocket->m_bDiscarded, true);
}