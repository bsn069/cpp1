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

		// PostQueuedCompletionStatus 发过来一个空的单句柄数据，表示线程要退出了。
		if(!pSocket && !pDg)
		{
			// 程序要求退出
			return 0;
		}

		if(!bSuccess)
		{
			// 有错误发生了
			/*
			If *lpOverlapped is NULL and the function does not dequeue a completion packet from the completion port, 
			the return value is zero. The function does not store information in the variables pointed to by the lpNumberOfBytes and lpCompletionKey parameters. 
			To get extended error information, call GetLastError. If the function did not dequeue a completion packet because the wait timed out, 
			GetLastError returns WAIT_TIMEOUT.
			*/
			if(!pDg)
			{
				// 目前应该不会进
			}
		}	

		pDg = (CFBNetwork_T_Dg*)((char*)pDg - 4);

		// 分别处理各种操作情况
		switch(pDg->m_OP)
		{
		case CFBNetwork_T_Dg::OP_CONNECT:
			{
				// ************************错误处理
				if(!bSuccess)
				{
					FB_DELETE(pDg);
					pT->Close(&pSocket);

					break;
				}
				// ************************错误处理

				int nRet;
				{
					// 保证下面流程不会被Close干扰		
					CFBKernel_MutexGuard Guard(&pSocket->m_Mutex);

					setsockopt(pSocket->m_Socket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, 0, 0);

					// 得到IP Port
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

					// 发出 WSARecv 请求
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
				// ************************错误处理
				if(!bSuccess)
				{
					SOCKET Socket = (SOCKET)(pDg->m_Buffer.len);
					//shutdown(Socket, SD_BOTH);
					closesocket(Socket);

					FB_DELETE(pDg);

					// 先临时用这种
					if(!pSocket->AcceptEx())
					{
						pT->Close(&pSocket);
					}

					// 下面的代码有问题，第一个判断自己关闭和返回错误都会进，在xp系统上自己关闭lasterror是有值，但是外网系统是0
					// 两种情况
					/*
					if(dwBytes == 0)
					{
						// 监听Socket断了，但是如果跳过去还是可以继续监听的
						// 删除监听的socket
						printf("fuck %d %d %d %d\n", dwBytes, (DWORD)(DWORD_PTR)pSocket, (DWORD)(DWORD_PTR)pDg, WSAGetLastError());
						pT->Close(&pSocket);
					}
					else
					{
						// 这次AcceptEx失败
						// 再抛出一个AcceptEx
						if(!pSocket->AcceptEx())
						{
							printf("suck %d %d %d %d\n", dwBytes, (DWORD)(DWORD_PTR)pSocket, (DWORD)(DWORD_PTR)pDg, WSAGetLastError());
							pT->Close(&pSocket);
						}
					}
					*/
					break;
				}
				// ************************错误处理
			
				SOCKET Socket = (SOCKET)(pDg->m_Buffer.len);

				// 设置一些参数
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

				// 创建一个新的用户
				CFBNetwork_T_Socket* pNewSocket = pT->NewSocket();
				pNewSocket->Open(Socket, CFBNetwork_T_Socket::S_ESTABLISHED);

				// 得到IP Port
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

				// 将新建立的套接字关联到完成端口
				CreateIoCompletionPort(
					(HANDLE)pNewSocket->m_Socket,
					pT->m_hIOCP,
					(DWORD_PTR)pNewSocket,
					0);

				++pNewSocket->m_dwUses;

				// 分配新Dg
				pDg->m_Buffer.len = CFBNetwork_T_Dg::BUF_SIZE;
				pDg->m_OP = CFBNetwork_T_Dg::OP_RECV;

				// 发出 WSARecv 请求
				DWORD dwTemp[2] = {0, 0};
				int nRet = WSARecv(
					pNewSocket->m_Socket,
					&pDg->m_Buffer,
					1,
					&dwTemp[0],
					&dwTemp[1],
					&pDg->m_Overlapped,
					0);

				// 不管错对都要发出系统通知
				pSocket->m_Accepts.Push(pNewSocket);

				// 必须先发出系统通知，再判断
				if(nRet == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
				{
					FB_DELETE(pDg);
					pT->Close(&pNewSocket);

					// 继续下去，因为这时候新用户已经创建了，必须要让上层知道，然后上层负责删除掉
				}

				// 再抛出一个AcceptEx
				if(!pSocket->AcceptEx())
				{
					pT->Close(&pSocket);
				}
			}
			break;
		case CFBNetwork_T_Dg::OP_SEND:
			{
				InterlockedExchangeAdd(&pSocket->m_lFluxOut, -(LONG)dwBytes);

				// ************************错误处理
				// 这里情况MSDN说的很隐晦，测试会有这种情况出现，就是成功了，但是dwBytes == 0
				if(!bSuccess || dwBytes == 0)
				{
					FB_DELETE(pDg);
					pT->Close(&pSocket);
					break;
				}
				// ************************错误处理

				FB_DELETE(pDg);
				pT->Close(&pSocket, false);
			}
			break;
		case CFBNetwork_T_Dg::OP_RECV:
			{
				// ************************错误处理
				// 这里情况MSDN说的很隐晦，测试会有这种情况出现，就是成功了，但是dwBytes == 0
				if(!bSuccess || dwBytes == 0) 
				{
					FB_DELETE(pDg);
					pT->Close(&pSocket);
					break;
				}
				// ************************错误处理

				pDg->m_Buffer.len = dwBytes;
				pSocket->m_Dgs.Push(pDg);

				// 分配新Dg
				CFBNetwork_T_Dg* pDg = FB_NEW(CFBNetwork_T_Dg, 1);
				pDg->m_Buffer.len = CFBNetwork_T_Dg::BUF_SIZE;
				pDg->m_OP = CFBNetwork_T_Dg::OP_RECV;

				int nRet;
				{
					// 保证下面流程不会被Close干扰		
					CFBKernel_MutexGuard Guard(&pSocket->m_Mutex);

					// 发出 WSARecv 请求
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
				// 继续发送 AcceptEx
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

	// 创建工作者线程
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
	// 等待所有用户离开
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

	// 结束工作者线程
	for(DWORD n = 0; n < m_Threads.Size(); n++)
	{
		PostQueuedCompletionStatus(m_hIOCP, 0, 0, 0);
	}
	// 等待线程结束
	WaitForMultipleObjects(m_Threads.Size(), m_Threads.Ptr(), true, INFINITE);

	for(DWORD n = 0; n < m_Threads.Size(); n++)
	{
		CloseHandle(m_Threads[n]);
	}
	m_Threads.Release();

	// 其他
	if(m_hIOCP)
	{
		CloseHandle(m_hIOCP);
		m_hIOCP = 0;
	}
}

CFBNetwork_T_Socket* CFBNetwork_T::Listen(sockaddr_in* pAddr)
{
	// 创建监听 SOCKET
	SOCKET Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, 0, 0, WSA_FLAG_OVERLAPPED);
	if(Socket == INVALID_SOCKET)
	{
		return 0;
	}

	// 设置一些参数
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

	// 创建
	CFBNetwork_T_Socket* pSocket = NewSocket();
	pSocket->Open(Socket, CFBNetwork_T_Socket::S_ESTABLISHED);

	// 将监听套接字和已经建立的完成端口关联起来
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

	// 将 FD_ACCEPT 事件注册到 Event，这样当可用 AcceptEx 调用被耗尽的时候，就会触发 FD_ACCEPT 事件
	//pSocket->m_pAcceptExEvent[0] = CreateEvent(0, false, false, 0);
	//pSocket->m_pAcceptExEvent[1] = CreateEvent(0, false, false, 0);

	// 创建线程
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

	// 设置一些参数
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

	// 绑定地址
	sockaddr_in Addr;
	Addr.sin_family = AF_INET;
	Addr.sin_addr.s_addr = htonl(INADDR_ANY);
	Addr.sin_port = 0;

	if(::bind(Socket, (const sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR)
	{
		return false;
	}

	// 创建
	CFBNetwork_T_Socket* pSocket = NewSocket();
	pSocket->Open(Socket, CFBNetwork_T_Socket::S_CONNECTING);

	// 挂接到完成端口
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
					// 删除这个重叠结构
					pNode->DeleteOver(pOver);
					// 删除这个用户
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

				// 更新连接进来的Socket
				/*
				setsockopt(
					pNewSocket->m_Socket, 
					SOL_SOCKET,
					SO_UPDATE_ACCEPT_CONTEXT,
					(char*)&pSocket->m_Socket,
					sizeof(pSocket->m_Socket));
				*/
