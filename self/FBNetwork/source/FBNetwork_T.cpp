#include "../include/FBNetwork_Port.h"

DWORD FBNetwork_T_WorkerThread(LPVOID pParam)
{
	CFBNetwork_T* pT = (CFBNetwork_T*)pParam;

	CFBNetwork_T_Socket* pSocket;
	CFBNetwork_T_Dg* pDg;

	DWORD dwBytes;

	while(1)
	{
		BOOL bSuccess = GetQueuedCompletionStatus(
			pT->m_hIOCP,
			&dwBytes,
			(PULONG_PTR)&pSocket,
			(LPOVERLAPPED*)&pDg,
			INFINITE);

		// PostQueuedCompletionStatus ������һ���յĵ�������ݣ���ʾ�߳�Ҫ�˳��ˡ�
		if(!pSocket && !pDg)
		{
			// ����Ҫ���˳�
			return 0;
		}

		if(!bSuccess)
		{
			// �д�������
			/*
			If *lpOverlapped is NULL and the function does not dequeue a completion packet from the completion port, 
			the return value is zero. The function does not store information in the variables pointed to by the lpNumberOfBytes and lpCompletionKey parameters. 
			To get extended error information, call GetLastError. If the function did not dequeue a completion packet because the wait timed out, 
			GetLastError returns WAIT_TIMEOUT.
			*/
			if(!pDg)
			{
				// ĿǰӦ�ò����
			}
		}	

		pDg = (CFBNetwork_T_Dg*)((char*)pDg - 4);

		// �ֱ�����ֲ������
		switch(pDg->m_OP)
		{
		case CFBNetwork_T_Dg::OP_CONNECT:
			{
				// ************************������
				if(!bSuccess)
				{
					FB_DELETE(pDg);
					pT->Close(&pSocket);

					break;
				}
				// ************************������

				int nRet;
				{
					// ��֤�������̲��ᱻClose����		
					CFBKernel_MutexGuard Guard(&pSocket->m_Mutex);

					setsockopt(pSocket->m_Socket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, 0, 0);

					// �õ�IP Port
					char* pBuffer = FB_NEW(char, 28);
					sockaddr_in* pLocalAddr = (sockaddr_in*)pBuffer;
					int nLocalAddr = sizeof(sockaddr_in) + 16;
					if(getsockname(pSocket->m_Socket, (sockaddr*)pLocalAddr, &nLocalAddr) != SOCKET_ERROR)
					{
						pSocket->m_LocalIP.m_dwIP = ntohl(pLocalAddr->sin_addr.s_addr);
						pSocket->m_wLocalPort = ntohs(pLocalAddr->sin_port);

/*
						printf(
							"local:%d.%d.%d.%d %d", 
							LocalAddr.sin_addr.S_un.S_un_b.s_b1,
							LocalAddr.sin_addr.S_un.S_un_b.s_b2,
							LocalAddr.sin_addr.S_un.S_un_b.s_b3,
							LocalAddr.sin_addr.S_un.S_un_b.s_b4,
							ntohs(LocalAddr.sin_port));
*/
					}

					sockaddr_in* pRemoteAddr = (sockaddr_in*)pBuffer;
					int nRemoteAddr = 28;
					if(getpeername(pSocket->m_Socket, (sockaddr*)pRemoteAddr, &nRemoteAddr) != SOCKET_ERROR)
					{
						pSocket->m_RemoteIP.m_dwIP = ntohl(pRemoteAddr->sin_addr.s_addr);
						pSocket->m_wRemotePort = ntohs(pRemoteAddr->sin_port);

						/*
						char aa[256];
						sprintf(
							aa,
							"remote:%d.%d.%d.%d %d", 
							RemoteAddr.sin_addr.S_un.S_un_b.s_b1,
							RemoteAddr.sin_addr.S_un.S_un_b.s_b2,
							RemoteAddr.sin_addr.S_un.S_un_b.s_b3,
							RemoteAddr.sin_addr.S_un.S_un_b.s_b4,
							ntohs(RemoteAddr.sin_port));
						MessageBoxA(0, aa, aa, MB_OK);
						*/
					}
					FB_DELETE(pBuffer);

					//
					pSocket->m_State = CFBNetwork_T_Socket::S_ESTABLISHED;

					// ���� WSARecv ����
					pDg->m_Buffer.len = CFBNetwork_T_Dg::BUF_SIZE;
					pDg->m_OP = CFBNetwork_T_Dg::OP_RECV;

					DWORD dwTemp[2] = {0};
					nRet = WSARecv(
						pSocket->m_Socket,
						&pDg->m_Buffer,
						1,
						&dwTemp[0],
						&dwTemp[1],
						&pDg->m_Overlapped,
						0);
				}

				if(nRet == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
				{
					FB_DELETE(pDg);
					pT->Close(&pSocket);
					break;
				}
			}
			break;
		case CFBNetwork_T_Dg::OP_ACCEPT:
			{
				// ************************������
				if(!bSuccess)
				{
					SOCKET Socket = (SOCKET)(pDg->m_Buffer.len);
					//shutdown(Socket, SD_BOTH);
					closesocket(Socket);

					FB_DELETE(pDg);

					// ����ʱ������
					if(!pSocket->AcceptEx())
					{
						pT->Close(&pSocket);
					}

					// ����Ĵ��������⣬��һ���ж��Լ��رպͷ��ش��󶼻������xpϵͳ���Լ��ر�lasterror����ֵ����������ϵͳ��0
					// �������
					/*
					if(dwBytes == 0)
					{
						// ����Socket���ˣ������������ȥ���ǿ��Լ���������
						// ɾ��������socket
						printf("fuck %d %d %d %d\n", dwBytes, (DWORD)(DWORD_PTR)pSocket, (DWORD)(DWORD_PTR)pDg, WSAGetLastError());
						pT->Close(&pSocket);
					}
					else
					{
						// ���AcceptExʧ��
						// ���׳�һ��AcceptEx
						if(!pSocket->AcceptEx())
						{
							printf("suck %d %d %d %d\n", dwBytes, (DWORD)(DWORD_PTR)pSocket, (DWORD)(DWORD_PTR)pDg, WSAGetLastError());
							pT->Close(&pSocket);
						}
					}
					*/
					break;
				}
				// ************************������
			
				SOCKET Socket = (SOCKET)(pDg->m_Buffer.len);

				// ����һЩ����
				BOOL bKeepAlive = true;     
				setsockopt(Socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(BOOL));     

				tcp_keepalive  In, Out;
				In.onoff = 1;
				In.keepalivetime = 1000;
				In.keepaliveinterval = 5000;

				DWORD dwRetBytes;     
				WSAIoctl(
					Socket,
					SIO_KEEPALIVE_VALS,
					(LPVOID)&In,
					sizeof(tcp_keepalive),
					(LPVOID)&Out,
					sizeof(tcp_keepalive),
					&dwRetBytes,
					0,
					0);

				int nREUSEADDR = 1;
				setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&nREUSEADDR, sizeof(int));

				linger Linger;
				Linger.l_onoff = 1;
				Linger.l_linger = 10;
				setsockopt(Socket, SOL_SOCKET, SO_LINGER, (const char*)&Linger, sizeof(linger));

				BOOL bNoDelay = true;
				setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&bNoDelay, sizeof(BOOL));

				// ����һ���µ��û�
				CFBNetwork_T_Socket* pNewSocket = pT->NewSocket();
				pNewSocket->Open(Socket, CFBNetwork_T_Socket::S_ESTABLISHED);

				// �õ�IP Port
				int nLocalAddr;
				sockaddr_in* pLocalAddr;
				int nRemoteAddr;
				sockaddr_in* pRemoteAddr;

				pT->m_pGetAcceptExSocketaddrs(
					pDg->m_Buffer.buf,
					0,
					sizeof(SOCKADDR_IN) + 16,
					sizeof(SOCKADDR_IN) + 16,
					(PSOCKADDR*)&pLocalAddr,
					&nLocalAddr,
					(PSOCKADDR*)&pRemoteAddr,
					&nRemoteAddr);
				if(pLocalAddr && pRemoteAddr)
				{
					pNewSocket->m_LocalIP.m_dwIP = ntohl(pLocalAddr->sin_addr.s_addr);
					pNewSocket->m_wLocalPort = ntohs(pLocalAddr->sin_port);

					pNewSocket->m_RemoteIP.m_dwIP = ntohl(pRemoteAddr->sin_addr.s_addr);
					pNewSocket->m_wRemotePort = ntohs(pRemoteAddr->sin_port);
				}

				// ���½������׽��ֹ�������ɶ˿�
				CreateIoCompletionPort(
					(HANDLE)pNewSocket->m_Socket,
					pT->m_hIOCP,
					(DWORD_PTR)pNewSocket,
					0);

				++pNewSocket->m_dwUses;

				// ������Dg
				pDg->m_Buffer.len = CFBNetwork_T_Dg::BUF_SIZE;
				pDg->m_OP = CFBNetwork_T_Dg::OP_RECV;

				// ���� WSARecv ����
				DWORD dwTemp[2] = {0, 0};
				int nRet = WSARecv(
					pNewSocket->m_Socket,
					&pDg->m_Buffer,
					1,
					&dwTemp[0],
					&dwTemp[1],
					&pDg->m_Overlapped,
					0);

				// ���ܴ�Զ�Ҫ����ϵͳ֪ͨ
				pSocket->m_Accepts.Push(pNewSocket);

				// �����ȷ���ϵͳ֪ͨ�����ж�
				if(nRet == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
				{
					FB_DELETE(pDg);
					pT->Close(&pNewSocket);

					// ������ȥ����Ϊ��ʱ�����û��Ѿ������ˣ�����Ҫ���ϲ�֪����Ȼ���ϲ㸺��ɾ����
				}

				// ���׳�һ��AcceptEx
				if(!pSocket->AcceptEx())
				{
					pT->Close(&pSocket);
				}
			}
			break;
		case CFBNetwork_T_Dg::OP_SEND:
			{
				InterlockedExchangeAdd(&pSocket->m_lFluxOut, -(LONG)dwBytes);

				// ************************������
				// �������MSDN˵�ĺ����ޣ����Ի�������������֣����ǳɹ��ˣ�����dwBytes == 0
				if(!bSuccess || dwBytes == 0)
				{
					FB_DELETE(pDg);
					pT->Close(&pSocket);
					break;
				}
				// ************************������

				FB_DELETE(pDg);
				pT->Close(&pSocket, false);
			}
			break;
		case CFBNetwork_T_Dg::OP_RECV:
			{
				// ************************������
				// �������MSDN˵�ĺ����ޣ����Ի�������������֣����ǳɹ��ˣ�����dwBytes == 0
				if(!bSuccess || dwBytes == 0) 
				{
					FB_DELETE(pDg);
					pT->Close(&pSocket);
					break;
				}
				// ************************������

				pDg->m_Buffer.len = dwBytes;
				pSocket->m_Dgs.Push(pDg);

				// ������Dg
				CFBNetwork_T_Dg* pDg = FB_NEW(CFBNetwork_T_Dg, 1);
				pDg->m_Buffer.len = CFBNetwork_T_Dg::BUF_SIZE;
				pDg->m_OP = CFBNetwork_T_Dg::OP_RECV;

				int nRet;
				{
					// ��֤�������̲��ᱻClose����		
					CFBKernel_MutexGuard Guard(&pSocket->m_Mutex);

					// ���� WSARecv ����
					DWORD dwTemp[2] = {0, 0};
					nRet = WSARecv(
						pSocket->m_Socket,
						&pDg->m_Buffer,
						1,
						&dwTemp[0],
						&dwTemp[1],
						&pDg->m_Overlapped,
						0);
				}

				if(nRet == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
				{
					FB_DELETE(pDg);
					pT->Close(&pSocket);
					break;
				}
			}
			break;
		}
	}
	return 0;
}
/*DWORD FBNetwork_T_AcceptThread(LPVOID pParam)
{
	CFBNetwork_T_Socket* pSocket = (CFBNetwork_T_Socket*)pParam;

	while(1)
	{
		switch(WSAWaitForMultipleEvents(2, pSocket->m_pAcceptExEvent, false, INFINITE, false))
		{
		case WSA_WAIT_EVENT_0:
			{
				// �������� AcceptEx
				pSocket->PostAcceptEx();
			}
			break;
		case WSA_WAIT_EVENT_0 + 1:
			{
				return 0;
			}
			break;
		}
	}
	return 0;
}
*/
CFBNetwork_T_Socket* CFBNetwork_T::NewSocket(void)
{
	CFBNetwork_T_Socket* pSocket = FB_NEW(CFBNetwork_T_Socket, 1);
	pSocket->m_pT = this;
	InterlockedIncrement((LONG volatile*)&m_dwSockets);
	return pSocket;
}

CFBNetwork_T::CFBNetwork_T()
{
	m_hIOCP = 0;
	m_dwSockets = 0;
}
CFBNetwork_T::~CFBNetwork_T()
{
	Quit();
}

BOOL CFBNetwork_T::Init(int nIOCPThreads, DWORD dwThreads)
{
	SOCKET Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, 0, 0, WSA_FLAG_OVERLAPPED);
	if(Socket == INVALID_SOCKET)
	{
		return false;
	}

	DWORD dwResult;
	GUID GetAcceptExSockaddrsGUID = WSAID_GETACCEPTEXSOCKADDRS;
	if(WSAIoctl(
		Socket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GetAcceptExSockaddrsGUID,
		sizeof(GetAcceptExSockaddrsGUID),
		&m_pGetAcceptExSocketaddrs,
		sizeof(m_pGetAcceptExSocketaddrs),
		&dwResult,
		0,
		0) == SOCKET_ERROR)
	{
		return false;
	}

	GUID ConnectExGuid = WSAID_CONNECTEX;
	if(WSAIoctl(
		Socket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&ConnectExGuid,
		sizeof(ConnectExGuid),
		&m_pConnectEx,
		sizeof(m_pConnectEx),
		&dwResult,
		0,
		0) == SOCKET_ERROR)
	{
		return false;
	}

	//shutdown(Socket, SD_BOTH);
	closesocket(Socket);

	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, nIOCPThreads);
	if(!m_hIOCP)
	{
		return false;
	}

	// �����������߳�
	DWORD dwThreadID;
	for(DWORD n = 0; n < dwThreads; n++)
	{
		m_Threads() = CreateThread(
			0,
			0, 
			(LPTHREAD_START_ROUTINE)FBNetwork_T_WorkerThread,
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
void CFBNetwork_T::Quit(void)
{
	// �ȴ������û��뿪
	CFBKernel_FPS FPS;
	FPS.SetDelay(1.0);

	while(1)
	{
		FPS.Delay();
		
		printf("left sockets: %d\n", m_dwSockets);

		if(m_dwSockets == 0)
		{
			break;
		}
	}

	// �����������߳�
	for(DWORD n = 0; n < m_Threads.Size(); n++)
	{
		PostQueuedCompletionStatus(m_hIOCP, 0, 0, 0);
	}
	// �ȴ��߳̽���
	WaitForMultipleObjects(m_Threads.Size(), m_Threads.Ptr(), true, INFINITE);

	for(DWORD n = 0; n < m_Threads.Size(); n++)
	{
		CloseHandle(m_Threads[n]);
	}
	m_Threads.Release();

	// ����
	if(m_hIOCP)
	{
		CloseHandle(m_hIOCP);
		m_hIOCP = 0;
	}
}

CFBNetwork_T_Socket* CFBNetwork_T::Listen(sockaddr_in* pAddr)
{
	// �������� SOCKET
	SOCKET Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, 0, 0, WSA_FLAG_OVERLAPPED);
	if(Socket == INVALID_SOCKET)
	{
		return 0;
	}

	// ����һЩ����
	BOOL bKeepAlive = true;     
	setsockopt(Socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(BOOL));     

	tcp_keepalive  In, Out;
	In.onoff = 1;
	In.keepalivetime = 1000;
	In.keepaliveinterval = 5000;

	DWORD dwBytes;     
	WSAIoctl(
		Socket,
		SIO_KEEPALIVE_VALS,
		(LPVOID)&In,
		sizeof(tcp_keepalive),
		(LPVOID)&Out,
		sizeof(tcp_keepalive),
		&dwBytes,
		0,
		0);

	int nREUSEADDR = 1;
	setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&nREUSEADDR, sizeof(int));

	linger Linger;
	Linger.l_onoff = 1;
	Linger.l_linger = 10;
	setsockopt(Socket, SOL_SOCKET, SO_LINGER, (const char*)&Linger, sizeof(linger));

	BOOL bNoDelay = true;
	setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&bNoDelay, sizeof(BOOL));

	// ����
	CFBNetwork_T_Socket* pSocket = NewSocket();
	pSocket->Open(Socket, CFBNetwork_T_Socket::S_ESTABLISHED);

	// �������׽��ֺ��Ѿ���������ɶ˿ڹ�������
	if(!CreateIoCompletionPort(
		(HANDLE)pSocket->m_Socket,
		m_hIOCP,
		(DWORD_PTR)pSocket,
		0))
	{
		return 0;
	}

	if(::bind(pSocket->m_Socket, (const sockaddr*)pAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		return 0;
	}	

	// �� FD_ACCEPT �¼�ע�ᵽ Event������������ AcceptEx ���ñ��ľ���ʱ�򣬾ͻᴥ�� FD_ACCEPT �¼�
	//pSocket->m_pAcceptExEvent[0] = CreateEvent(0, false, false, 0);
	//pSocket->m_pAcceptExEvent[1] = CreateEvent(0, false, false, 0);

	// �����߳�
	/*DWORD dwThreadID;
	pSocket->m_hAcceptThread = CreateThread(
		0,
		0, 
		(LPTHREAD_START_ROUTINE)FBNetwork_T_AcceptThread,
		pSocket,
		0,
		&dwThreadID);
	if(!pSocket->m_hAcceptThread)
	{
		return 0;
	}

	pSocket->m_dwAcceptExs = dwAcceptExs;
	if(WSAEventSelect(pSocket->m_Socket, pSocket->m_pAcceptExEvent[0], FD_ACCEPT) == SOCKET_ERROR)
	{
		return 0;
	}*/

	if(listen(pSocket->m_Socket, SOMAXCONN) == SOCKET_ERROR)
	{
		return 0;
	}

	//pSocket->PostAcceptEx();

	++pSocket->m_dwUses;
	if(!pSocket->AcceptEx())
	{
		Close(&pSocket);
	}

	return pSocket;
}

CFBNetwork_T_Socket* CFBNetwork_T::Connect(sockaddr_in* pAddr)
{
	SOCKET Socket = WSASocket(
		AF_INET, 
		SOCK_STREAM, 
		IPPROTO_IP,
		0,
		0,
		WSA_FLAG_OVERLAPPED);
	if(Socket == INVALID_SOCKET)
	{
		return 0;
	}

	// ����һЩ����
	BOOL bKeepAlive = true;     
	setsockopt(Socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(BOOL));     

	tcp_keepalive  In, Out;
	In.onoff = 1;
	In.keepalivetime = 1000;
	In.keepaliveinterval = 5000;

	DWORD dwBytes;     
	WSAIoctl(
		Socket,
		SIO_KEEPALIVE_VALS,
		(LPVOID)&In,
		sizeof(tcp_keepalive),
		(LPVOID)&Out,
		sizeof(tcp_keepalive),
		&dwBytes,
		0,
		0);

	int nReuseAddr = 1;
	setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&nReuseAddr, sizeof(int));

	linger Linger;
	Linger.l_onoff = 1;
	Linger.l_linger = 10;
	setsockopt(Socket, SOL_SOCKET, SO_LINGER, (const char*)&Linger, sizeof(linger));

	BOOL bNoDelay = true;
	setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&bNoDelay, sizeof(BOOL));

	// �󶨵�ַ
	sockaddr_in Addr;
	Addr.sin_family = AF_INET;
	Addr.sin_addr.s_addr = htonl(INADDR_ANY);
	Addr.sin_port = 0;

	if(::bind(Socket, (const sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR)
	{
		return false;
	}

	// ����
	CFBNetwork_T_Socket* pSocket = NewSocket();
	pSocket->Open(Socket, CFBNetwork_T_Socket::S_CONNECTING);

	// �ҽӵ���ɶ˿�
	if(!CreateIoCompletionPort(
		(HANDLE)pSocket->m_Socket,
		m_hIOCP,
		(DWORD_PTR)pSocket,
		0))
	{
		return false;
	}

	++pSocket->m_dwUses;

	CFBNetwork_T_Dg* pDg = FB_NEW(CFBNetwork_T_Dg, 1);
	pDg->m_OP = CFBNetwork_T_Dg::OP_CONNECT;

	if(
		!m_pConnectEx(pSocket->m_Socket, (PSOCKADDR)pAddr, sizeof(sockaddr_in), 0, 0, 0, &pDg->m_Overlapped) &&
		WSAGetLastError() != ERROR_IO_PENDING)
	{
		return false;
	}
	return pSocket;
}
void CFBNetwork_T::Close(CFBNetwork_T_Socket** pSocket, BOOL bForce)
{
	if(!*pSocket)
	{
		return;
	}

	if((*pSocket)->Close(bForce))
	{
		FB_DELETE(*pSocket);
		InterlockedDecrement((LONG volatile*)&m_dwSockets);
	}
	else
	{
		*pSocket = 0;
	}
}









				// IP
				/*
				int nLocalAddr;
				int nRemoteAddr;

				LPSOCKADDR pLocalAddr;
				sockaddr_in* pRemoteAddr = 0;

				pT->m_pGetAcceptExSocketaddrs(
					pDg->m_Buffer.buf,
					0,
					sizeof(SOCKADDR_IN) + 16,
					sizeof(SOCKADDR_IN) + 16,
					(PSOCKADDR*)&pLocalAddr,
					&nLocalAddr,
					(PSOCKADDR*)&pRemoteAddr,
					&nRemoteAddr);
					*/

				/*
				if(!pRemoteAddr)
				{
					// ɾ������ص��ṹ
					pNode->DeleteOver(pOver);
					// ɾ������û�
					pIOCP->DeleteNode(pNewNode, 0);
					break;
				}

				sprintf(
					pNewNode->m_pIP, 
					"%d.%d.%d.%d", 
					pRemoteAddr->sin_addr.S_un.S_un_b.s_b1,
					pRemoteAddr->sin_addr.S_un.S_un_b.s_b2,
					pRemoteAddr->sin_addr.S_un.S_un_b.s_b3,
					pRemoteAddr->sin_addr.S_un.S_un_b.s_b4);

				CopyMemory(pNewNode->m_byIP, &pRemoteAddr->sin_addr.S_un.S_un_b.s_b1, 4);
				*/

				// �������ӽ�����Socket
				/*
				setsockopt(
					pNewSocket->m_Socket, 
					SOL_SOCKET,
					SO_UPDATE_ACCEPT_CONTEXT,
					(char*)&pSocket->m_Socket,
					sizeof(pSocket->m_Socket));
				*/
