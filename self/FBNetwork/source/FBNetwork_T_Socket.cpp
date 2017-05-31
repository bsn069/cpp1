#include "../include/FBNetwork_Port.h"

void CFBNetwork_T_Socket::Open(SOCKET Socket, STATE State)
{
	m_Socket = Socket;
	m_State = State;

	++m_dwUses;
}
BOOL CFBNetwork_T_Socket::Close(BOOL bForce)
{
	CFBKernel_MutexGuard Guard(&m_Mutex);

	if(bForce && m_Socket != INVALID_SOCKET)
	{
		//shutdown(m_Socket, SD_BOTH);
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;

		m_State = CFBNetwork_T_Socket::S_CLOSE;

		/*
		if(m_hAcceptThread)
		{
			WSASetEvent(m_pAcceptExEvent[1]);
			WaitForSingleObject(m_hAcceptThread, INFINITE);
			CloseHandle(m_hAcceptThread);
			m_hAcceptThread = 0;

			CloseHandle(m_pAcceptExEvent[0]);
			m_pAcceptExEvent[0] = 0;

			CloseHandle(m_pAcceptExEvent[1]);
			m_pAcceptExEvent[0] = 0;
		}*/
	}
	return --m_dwUses == 0;
}

/*
void CFBNetwork_T_Socket::SetState(STATE State)
{
	lock_guard<recursive_mutex> ShareGuard(m_Mutex);

	if(State == S_ESTABLISHED)
	{
		int nLen = sizeof(sockaddr_in);

		getsockname(m_Socket, (sockaddr*)&m_LocalAddr, &nLen);
		getpeername(m_Socket, (sockaddr*)&m_RemoteAddr, &nLen);
	}
	m_State = State;
}
*/

/*void CFBNetwork_T_Socket::PostAcceptEx(void)
{
	lock_guard<recursive_mutex> ShareGuard(m_Mutex);

	for(DWORD n = 0; n < m_dwAcceptExs; n++)
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
			return;
		}

		CFBNetwork_T_Dg* pDg = FB_NEW(CFBNetwork_T_Dg, 1);

		pDg->m_Buffer.len = (DWORD)Socket;
		pDg->m_OP = CFBNetwork_T_Dg::OP_ACCEPT;

		DWORD dwBytes;
		if(!AcceptEx(
			m_Socket,
			Socket,
			pDg->m_Buffer.buf,
			0,
			sizeof(SOCKADDR_IN) + 16,
			sizeof(SOCKADDR_IN) + 16,
			&dwBytes,
			&pDg->m_Overlapped))
		{
			if(WSAGetLastError() != ERROR_IO_PENDING)
			{
				//shutdown(Socket, SD_BOTH);
				closesocket(Socket);

				FB_DELETE(pDg);
				return;
			}
		}
		++m_dwUses;
	}
}
*/
BOOL CFBNetwork_T_Socket::AcceptEx(void)
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
		return false;
	}

	CFBNetwork_T_Dg* pDg = FB_NEW(CFBNetwork_T_Dg, 1);

	pDg->m_Buffer.len = (DWORD)Socket;
	pDg->m_OP = CFBNetwork_T_Dg::OP_ACCEPT;

	// 保证下面流程不会被Close干扰	
	CFBKernel_MutexGuard Guard(&m_Mutex);

	DWORD dwBytes;
	if(!::AcceptEx(
		m_Socket,
		Socket,
		pDg->m_Buffer.buf,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		&dwBytes,
		&pDg->m_Overlapped))
	{
		if(WSAGetLastError() != ERROR_IO_PENDING)
		{
			//shutdown(Socket, SD_BOTH);
			closesocket(Socket);

			FB_DELETE(pDg);
			return false;
		}
	}

	return true;
}

CFBNetwork_T_Socket::CFBNetwork_T_Socket()
{
	m_Socket = INVALID_SOCKET;

	m_LocalIP.m_dwIP = 0;
	m_wLocalPort = 0;
	m_RemoteIP.m_dwIP = 0;
	m_wRemotePort = 0;

	/*
	m_hAcceptThread = 0;
	m_pAcceptExEvent[0] = 0;
	m_pAcceptExEvent[1] = 0;*/

	m_dwUses = 0;

	InterlockedExchange(&m_lFluxOut, 0);

	m_pSendDg = 0;
}
CFBNetwork_T_Socket::~CFBNetwork_T_Socket()
{
	CFBKernel_Vector<CFBNetwork_T_Socket*>* pAccepts = m_Accepts.Flip();
	for(DWORD n = 0; n < pAccepts->Size(); ++n)
	{
		m_pT->Close(&(*pAccepts)[n]);
	}

	CFBKernel_Vector<CFBNetwork_T_Dg*>* pDgs = m_Dgs.Flip();
	for(DWORD n = 0; n < pDgs->Size(); ++n)
	{
		FB_DELETE((*pDgs)[n]);
	}

	if(m_pSendDg)
	{
		FB_DELETE(m_pSendDg);
	}
}

CFBNetwork_T_Socket::STATE CFBNetwork_T_Socket::State(void)
{
	CFBKernel_MutexGuard Guard(&m_Mutex);
	return m_State;
}

CFBKernel_Vector<CFBNetwork_T_Socket*>* CFBNetwork_T_Socket::Accepts(void)
{
	// 还要保证在Accepts中间State不会变为Close
	CFBKernel_MutexGuard Guard(&m_Mutex);
	return m_Accepts.Flip();
}

BOOL CFBNetwork_T_Socket::Send(char* pBuffer, DWORD dwLen)
{
	// 这个锁是为了保证多个线程调用Send保证每个Dg的顺序正确
	// 还要保证在Send中间State不会变为Close
	CFBKernel_MutexGuard Guard(&m_Mutex);

	if(m_State != S_ESTABLISHED)
	{
		return false;
	}

	// 将消息复制到当前over 
	DWORD dwCopyed = 0;
	while(1)
	{
		if(!m_pSendDg)
		{
			m_pSendDg = FB_NEW(CFBNetwork_T_Dg, 1);
			m_pSendDg->m_OP = CFBNetwork_T_Dg::OP_SEND;
		}

		DWORD dwBytes = __min(CFBNetwork_T_Dg::BUF_SIZE - m_pSendDg->m_Buffer.len, dwLen - dwCopyed);
		CopyMemory(
			m_pSendDg->m_pBuffer + m_pSendDg->m_Buffer.len,
			pBuffer + dwCopyed, 
			dwBytes);

		m_pSendDg->m_Buffer.len += dwBytes;
		dwCopyed += dwBytes;

		if(m_pSendDg->m_Buffer.len == CFBNetwork_T_Dg::BUF_SIZE)
		{
			if(!End())
			{
				return false;
			}
		}

		if(dwCopyed == dwLen)
		{
			break;
		}
	}
	return true;
}
BOOL CFBNetwork_T_Socket::Recv(CFBNetwork_Stuff* pStuff)
{
	// 还要保证在Recv中间State不会变为Close
	CFBKernel_MutexGuard Guard(&m_Mutex);

	pStuff->Release();

	// 计算总共接收了多少个字节
	CFBKernel_Vector<CFBNetwork_T_Dg*>* pVector = m_Dgs.Flip();
	for(DWORD n = 0; n < pVector->Size(); n++)
	{
		pStuff->Push((*pVector)[n]);
	}

	return m_State != S_CLOSE;
}

BOOL CFBNetwork_T_Socket::End(void)
{
	// 这个锁是为了保证多个线程调用Send保证每个Dg的顺序正确
	// 还要保证在Send中间State不会变为Close
	CFBKernel_MutexGuard Guard(&m_Mutex);

	if(m_pSendDg)
	{
		InterlockedExchangeAdd(&m_lFluxOut, (LONG)m_pSendDg->m_Buffer.len);

		// 发送over
		DWORD dwSent;
		int nRet = WSASend(m_Socket, &m_pSendDg->m_Buffer, 1, &dwSent, 0, &m_pSendDg->m_Overlapped, 0);
		if(nRet == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
		{
			InterlockedExchangeAdd(&m_lFluxOut, -(LONG)m_pSendDg->m_Buffer.len);

			FB_DELETE(m_pSendDg);
			return false;
		}

		++m_dwUses;

		m_pSendDg = 0;
	}

	return true;
}

 
