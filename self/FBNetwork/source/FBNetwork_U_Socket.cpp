#include "../include/FBNetwork_Port.h"

void CFBNetwork_U_Socket::Init(sockaddr_in* pAddr, DWORD dwID, CFBNetwork_U* pU)
{
	m_pU = pU;

	if(dwID == 0)
	{
		m_dwID = m_pU->ID(&m_RAddr);
		SetState(S_CONNECTING);
	}
	else
	{
		m_dwID = dwID;

		switch(m_pU->IDType(m_dwID))
		{
		case CFBNetwork_U::IDT_CS:
			{
				SetState(S_ESTABLISHED);
			}
			break;
		case CFBNetwork_U::IDT_P2P:
			{
				SetState(S_CONNECTING);
			}
			break;
		}
	}

	CopyMemory(&m_RAddr, pAddr, sizeof(sockaddr_in));

	m_dwLDatas = 0;
	m_dwRDatas = 0;

	m_dConnectTimer = 0.0;
	m_dwConnectTimes = 0;
	
	m_bDiscarded = false;
	m_bUsedByIS = false;

	m_OSNotify.m_pSocket = this;

	m_dwSEQ = 0;
	m_dwWanted = 0;

	m_dwLastACK = 0;
	m_dwLastACKs = 0;

	m_dwRBuffer = 65535;	
	m_dwRBufferNow = 0;
	
	m_RBytes = 0;

	m_dWndTimer = 0.0;
	m_dwAliveTimer = 0;
}

void CFBNetwork_U_Socket::SetState(STATE State)
{
	InterlockedExchange((LONG volatile*)&m_State, State);
	if(m_State == S_CLOSE)
	{
		m_Flux.Break();
		m_FDgs.Break();
	}
}

void CFBNetwork_U_Socket::SetUsedByIS(BOOL bTrue)
{
	InterlockedExchange((volatile LONG*)&m_bUsedByIS, bTrue);
}

void CFBNetwork_U_Socket::NotifyOS(void)
{
	lock_guard<mutex> Guard(m_SDgMutex);

	CFBNetwork_U_Dg* pDg = m_SDgs.GetHead();
	if(!pDg)
	{
		return;
	}

	// 第一个Dg可以发送就可以提交给OS了
	if(m_Flux.CanFlow(pDg->m_dwLen))
	{
		m_pU->m_OS.Push(&m_OSNotify);
	}
}

void CFBNetwork_U_Socket::SendTo(CFBNetwork_U_Dg* pDg)
{
	pDg->m_Content.m_dwID = m_dwID;

	sendto(                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
		m_pU->m_Socket, 
		(char*)&pDg->m_Content, 
		pDg->m_dwLen, 
		0, 
		(sockaddr*)&m_RAddr, 
		sizeof(sockaddr));
}

void CFBNetwork_U_Socket::OnAlive(void)
{
	if(InterlockedCompareExchange((LONG volatile*)&m_State, S_ESTABLISHED, S_CONNECTING) == S_CONNECTING && m_hConnectEvent)
	{
		SetEvent(m_hConnectEvent);
	}
	InterlockedExchange((LONG volatile*)&m_dwAliveTimer, 0);
}
void CFBNetwork_U_Socket::OnSEQ(CFBNetwork_U_Dg* pDg)
{
	BOOL bACKNow = false;
	DWORD dwSEQ = pDg->m_Content.m_dwSEQ;

	DWORD dwWanted = m_dwWanted;

	int nCmp = FBNETWORK_U_SEQ_CMP(dwSEQ, dwWanted);
	if(nCmp < 0)
	{
		// 收到一个之前已经确认过的报文
		FB_DELETE(pDg);

		// 立刻ACK
		bACKNow = true;
	}
	else if(nCmp == 0)
	{
		// 占用接收缓冲区
		InterlockedExchangeAdd((volatile LONG*)&m_dwRBufferNow, pDg->m_dwLen);

		// 收到希望的Dg直接放入FDgs
		m_FDgs.Push(pDg);

		// 把后面序号连续的Dg也处理了
		CFBNetwork_U_Dg* pRDg;
		SEQMap::iterator it;

		while(1)
		{
			// 这里可以考虑不是每次都原子操作（已修改）
			dwWanted++;

			if((it = m_RDgs.find(dwWanted)) == m_RDgs.end())
			{
				break;
			}

			pRDg = it->second;
			m_RDgs.erase(it);
			m_FDgs.Push(pRDg);

			// 因为到了这里就说明填补了之前丢失的报文，立刻ACK
			bACKNow = true;
		}

		InterlockedExchange((volatile LONG*)&m_dwWanted, dwWanted);

		// 通知有连续的消息可以读取了
		m_FDgs.Event();
	}
	else
	{
		// 收到一个比期望序号还大的Dg
		if(m_RDgs.find(dwSEQ) == m_RDgs.end())
		{
			// 占用接收缓冲区
			InterlockedExchangeAdd((volatile LONG*)&m_dwRBufferNow, pDg->m_dwLen);

			// 保存起来
			m_RDgs[dwSEQ] = pDg;
		}
		else
		{
			// 已经接收过这个Dg了
			FB_DELETE(pDg);
		}

		// 立刻ACK
		bACKNow = true;
	}

	if(++m_dwDelayACKs == DELAYACKS || bACKNow)
	{
		// 发送ACK
		CFBNetwork_U_Dg Dg;
		Dg.m_Content.m_dwSEQ = m_dwWanted;
		Dg.SetFlagWnd(CFBNetwork_U_Dg::ACK, m_dwRBuffer - m_dwRBufferNow);
		*((DWORD*)Dg.m_Content.m_pData) = dwSEQ;

		SendTo(&Dg);

		m_dwDelayACKs = 0;
	}
}
void CFBNetwork_U_Socket::OnACK(CFBNetwork_U_Dg* pDg)
{
#ifdef _FILE_LOG_
	fprintf(m_pU->m_pFile, "ACK %d", pDg->m_Content.m_dwSEQ);
#endif

	if(
		pDg->m_Content.m_dwSEQ < m_dwLastACK ||
		pDg->m_Content.m_dwSEQ > m_dwSEQ ||
		(pDg->m_Content.m_dwSEQ == m_dwSEQ && pDg->m_Content.m_dwSEQ == m_dwLastACK))
	{
		return;
	}

	CFBNetwork_U_Dg* pBDg;

	if(pDg->Flag() == CFBNetwork_U_Dg::ACK)
	{
		if(pDg->m_Content.m_dwSEQ == m_dwLastACK)
		{
			lock_guard<mutex> Guard(m_BDgMutex);

			if(++m_dwLastACKs == 4)
			{
				// 立刻发送
				pBDg = m_BDgs.GetHead();
				pBDg->m_dResendTimer = 0.0;

				SendTo(pBDg);

				m_Flux.OnLost();
			}
		}
		else
		{
			m_dwLastACK = pDg->m_Content.m_dwSEQ;
			m_dwLastACKs = 0;
		}
	}
	else
	{
		int a = 10;
	}

	DWORD dwBytes = 0;
	CFBNetwork_U_Dg* pBDgNext;

	{
		lock_guard<mutex> Guard(m_BDgMutex);

		pBDg = m_BDgs.GetHead();
		while(pBDg)
		{
			pBDgNext = m_BDgs.GetNext(pBDg);

			if(FBNETWORK_U_SEQ_CMP(pBDg->m_Content.m_dwSEQ, pDg->m_Content.m_dwSEQ) < 0)
			{
				dwBytes += pBDg->m_dwLen;

				m_Flux.OnACK();

				m_BDgs.Pop(pBDg);
				FB_DELETE(pBDg);
			}
			else if(pDg->Flag() == CFBNetwork_U_Dg::ACK && FBNETWORK_U_SEQ_CMP(pBDg->m_Content.m_dwSEQ, *((DWORD*)pDg->m_Content.m_pData)) == 0)
			{
				dwBytes += pBDg->m_dwLen;

				//m_Flux.OnACK();

				m_BDgs.Pop(pBDg);
				FB_DELETE(pBDg);

				// 这里还需要测试
				break;
			}

			pBDg = pBDgNext;
		}
	}

	m_Flux.Update(dwBytes, pDg->Wnd());

#ifdef _FILE_LOG_
	fprintf(m_pU->m_pFile, " RWND %d\n", m_Flux.m_dwRWnd);
#endif

	NotifyOS();
}
void CFBNetwork_U_Socket::OnWnd(CFBNetwork_U_Dg* pDg)
{
	m_Flux.Update(0, pDg->Wnd());

	NotifyOS();
}

void CFBNetwork_U_Socket::OnTimer_Connecting(double dElapsed)
{
	m_dConnectTimer += dElapsed;
	if(m_dConnectTimer >= 1.0)
	{
		m_dwConnectTimes++;
		if(m_dwConnectTimes >= 10)
		{
			// 连接失败
			SetState(CFBNetwork_U_Socket::S_CLOSE);
			SetEvent(m_hConnectEvent);
		}
		else
		{
			// 发送连接消息
			CFBNetwork_U_Dg Dg;
			Dg.SetFlagWnd(CFBNetwork_U_Dg::OPEN, m_dwRBuffer - m_dwRBufferNow);
			if(m_dwLDatas)
			{
				Dg.m_dwLen += m_dwLDatas;
				CopyMemory(Dg.m_Content.m_pData, &m_LData[0], m_dwLDatas);
			}

			SendTo(&Dg);
		}
		m_dConnectTimer = 0.0;
	}
}
void CFBNetwork_U_Socket::OnTimer_Established(double dElapsed)
{
	// 重发消息
	{
		BOOL bTimeout = false;

		lock_guard<mutex> Guard(m_BDgMutex);

		CFBNetwork_U_Dg* pDg = m_BDgs.GetHead();
		while(pDg)
		{
			pDg->m_dResendTimer += dElapsed;
			if(pDg->m_dResendTimer >= 1.0)
			{
				pDg->m_dResendTimer -= 1.0;
				SendTo(pDg);

				bTimeout = true;
			}
			pDg = m_BDgs.GetNext(pDg);
		}

		if(bTimeout)
		{
			m_Flux.OnTimeout();
		}
		//m_dwLastACKs = 0;
	}

	// 多少秒没有收到消息就证明断开了
	if(InterlockedExchangeAdd((LONG volatile*)&m_dwAliveTimer, (DWORD)(dElapsed * 1000.0)) >= 1000 * 30)
	{
		SetState(S_CLOSE);
		return;
	}

	// 发送WND
	m_dWndTimer += dElapsed;
	if(m_dWndTimer >= 0.5)
	{
		m_dWndTimer -= 0.5;

		CFBNetwork_U_Dg Dg;
		Dg.m_Content.m_dwSEQ = m_dwWanted;
		Dg.SetFlagWnd(CFBNetwork_U_Dg::WND, m_dwRBuffer - m_dwRBufferNow);

		SendTo(&Dg);
	}
}

CFBNetwork_U_Socket::~CFBNetwork_U_Socket()
{
	m_pU->Close(this);

	CFBNetwork_U_Dg* pDg;
	while(pDg = m_SDgs.GetHead())
	{
		m_SDgs.Pop(pDg);
		FB_DELETE(pDg);
	}
	while(pDg = m_BDgs.GetHead())
	{
		m_BDgs.Pop(pDg);
		FB_DELETE(pDg);
	}

	SEQMap::iterator it;
	for(it = m_RDgs.begin(); it != m_RDgs.end(); it++)
	{
		FB_DELETE(it->second);
	}

	CFBKernel_Vector<CFBNetwork_U_Dg*>* pDgs = m_FDgs.Flip();
	for(DWORD n = 0; n < pDgs->Size(); n++)
	{
		FB_DELETE((*pDgs)[n]);
	}
}

CFBNetwork_U_Socket::STATE CFBNetwork_U_Socket::State(void)
{
	return m_State;
}
sockaddr_in* CFBNetwork_U_Socket::RAddr(void)
{
	return &m_RAddr;
}
pair<char*, DWORD> CFBNetwork_U_Socket::RData(void)
{
	return pair<char*, DWORD>(&m_RData[0], m_dwRDatas);
}

BOOL CFBNetwork_U_Socket::Send(char* pBuffer, DWORD dwLen, BOOL bBlock)
{
	CFBNetwork_U_Flux_Notify* pNotify = 0;
	CFBKernel_List<CFBNetwork_U_Dg> SDgs;

	DWORD dwOffset = 0;
	DWORD dwCopy = 0;
	CFBNetwork_U_Dg* pDg;

	DWORD dwDgs = dwLen / CFBNetwork_U_Dg::BUFFERSIZE;
	if(dwLen % CFBNetwork_U_Dg::BUFFERSIZE)
	{
		dwDgs++;
	}

	DWORD dwBytes = dwDgs * CFBNetwork_U_Dg::HEADERSIZE + dwLen;
	pNotify = m_Flux.CheckIn(dwBytes, bBlock);

	for(DWORD n = 0; n < dwDgs; n++)
	{
		dwCopy = dwLen - dwOffset;
		dwCopy = dwCopy > CFBNetwork_U_Dg::BUFFERSIZE ? CFBNetwork_U_Dg::BUFFERSIZE : dwCopy;

		pDg = FB_NEW(CFBNetwork_U_Dg, 1);
		pDg->m_dwLen += dwCopy;
		pDg->SetFlagWnd(CFBNetwork_U_Dg::SEQ, 0);
		CopyMemory(pDg->m_Content.m_pData, pBuffer + dwOffset, dwCopy);

		dwOffset += dwCopy;

		SDgs.Push_Back(pDg);
	}

	{
		lock_guard<mutex> Guard(m_SDgMutex);
		m_SDgs.Merge(&SDgs);
	}

	NotifyOS();

	m_Flux.Wait(pNotify);

	return m_State != S_CLOSE;
}
BOOL CFBNetwork_U_Socket::Recv(CFBNetwork_Stuff* pStuff, BOOL bBlock)
{
	pStuff->~CFBNetwork_Stuff();

	BOOL bWnd = false;
	DWORD dwTotalBytes = 0;

	{
		unique_lock<mutex> Guard(m_RMutex, defer_lock);

		if(!bBlock)
		{
			if(Guard.try_lock())
			{
				goto __RECV;
			}
			return true;
		}

		Guard.lock();

		m_FDgs.Wait();

		__RECV:

		CFBKernel_Vector<CFBNetwork_U_Dg*>* pDgs = m_FDgs.Flip();

		// 计算总共接收了多少个字节
		for(DWORD n = 0; n < pDgs->Size(); n++)
		{
			pStuff->Push((*pDgs)[n]);
			dwTotalBytes += (*pDgs)[n]->m_dwLen;
		}

		m_RBytes += pStuff->m_dwBytes;
		if(m_RBytes >= 32768)
		{
			m_RBytes -= 32768;
			
			bWnd = true;
		}
	}

	// 释放接收缓冲区
	InterlockedExchangeAdd((volatile LONG*)&m_dwRBufferNow, -(int)dwTotalBytes);

	if(bWnd)
	{
		// 发送WND
		CFBNetwork_U_Dg Dg;
		Dg.m_Content.m_dwSEQ = m_dwWanted;
		Dg.SetFlagWnd(CFBNetwork_U_Dg::WND, m_dwRBuffer - m_dwRBufferNow);

		SendTo(&Dg);
	}

	return m_State != S_CLOSE;
}
