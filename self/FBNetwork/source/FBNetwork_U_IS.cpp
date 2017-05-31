#include "../include/FBNetwork_Port.h"

DWORD CFBNetwork_U_IS::Thread(CFBNetwork_U_IS* pIS)
{
	CFBNetwork_U* pU = pIS->m_pU;

	sockaddr_in Addr;
	int nLen = sizeof(sockaddr_in);
	DWORD dwBytes;

	while(1)
	{
		CFBNetwork_U_Dg* pDg = FB_NEW(CFBNetwork_U_Dg, 1);
		pDg->m_dwLen = CFBNetwork_U_Dg::TOTALSIZE;

		__RECV:

		dwBytes = recvfrom(
			pU->m_Socket,
			(char*)&pDg->m_Content,
			pDg->m_dwLen,
			0,
			(sockaddr*)&Addr,
			&nLen);

		if(pIS->m_bQuit)
		{
			FB_DELETE(pDg);
			break;
		}

		if(dwBytes == SOCKET_ERROR)
		{
			DWORD dwLastError = WSAGetLastError();
			if(dwLastError == 10060 || dwLastError == 10054)
			{
				goto __RECV;
			}
			FB_DELETE(pDg);
			break;
		}

		pDg->m_dwLen = dwBytes;
		pDg->m_Content.m_dwID = CFBNetwork_U::SwapID(pDg->m_Content.m_dwID);

		switch(pDg->Flag())
		{
		case CFBNetwork_U_Dg::OPEN:
			{
				CFBNetwork_U_Socket* pSocket = pU->QuerySocket(&Addr, pDg->m_Content.m_dwID, true);
				if(pSocket)
				{
					if(pSocket->m_State != CFBNetwork_U_Socket::S_CLOSE)
					{
						if(pSocket->m_State == CFBNetwork_U_Socket::S_CONNECTING)
						{
							// 新的P2PCONNECT
							pSocket->m_dwRDatas = pDg->m_dwLen - CFBNetwork_U_Dg::HEADERSIZE;
							pSocket->m_RData.Resize(pSocket->m_dwRDatas);
							CopyMemory(&pSocket->m_RData[0], pDg->m_Content.m_pData, pSocket->m_dwRDatas);

							pSocket->OnWnd(pDg);
							pSocket->OnAlive();
						}

						// 发送窗口消息
						CFBNetwork_U_Dg Dg;
						Dg.m_Content.m_dwSEQ = pSocket->m_dwWanted;
						Dg.SetFlagWnd(CFBNetwork_U_Dg::WND, pSocket->m_dwRBuffer - pSocket->m_dwRBufferNow);

						pSocket->SendTo(&Dg);

						pSocket->SetUsedByIS(false);
					}
				}
				else
				{
					if(pU->m_bListen)
					{
						// 新的CONNECT
						// 创建Socket
						pSocket = FB_NEW(CFBNetwork_U_Socket, 1);
						pSocket->Init(&Addr, pDg->m_Content.m_dwID, pU);
						pU->PushSocket(pSocket);

						pSocket->OnWnd(pDg);

						pSocket->m_dwRDatas = pDg->m_dwLen - CFBNetwork_U_Dg::HEADERSIZE;
						if(pSocket->m_dwRDatas)
						{
							pSocket->m_RData.Resize(pSocket->m_dwRDatas);
							CopyMemory(&pSocket->m_RData[0], pDg->m_Content.m_pData, pSocket->m_dwRDatas);
						}

						// 发送窗口消息
						CFBNetwork_U_Dg Dg;
						Dg.m_Content.m_dwSEQ = pSocket->m_dwWanted;
						Dg.SetFlagWnd(CFBNetwork_U_Dg::WND, pSocket->m_dwRBuffer - pSocket->m_dwRBufferNow);

						pSocket->SendTo(&Dg);

						// 给上层通知
						pU->m_Accepts.Push(pSocket);
					}
				}
				FB_DELETE(pDg);
			}
			break;
		case CFBNetwork_U_Dg::CLOSE:
			{
				CFBNetwork_U_Socket* pSocket = pU->QuerySocket(&Addr, pDg->m_Content.m_dwID, true);
				if(pSocket)
				{
					pSocket->SetState(CFBNetwork_U_Socket::S_CLOSE);
					pSocket->SetUsedByIS(false);
				}
				FB_DELETE(pDg);
			}
			break;
		case CFBNetwork_U_Dg::SEQ:
			{
				CFBNetwork_U_Socket* pSocket = pU->QuerySocket(&Addr, pDg->m_Content.m_dwID, true);
				if(pSocket)
				{
					if(pSocket->m_State != CFBNetwork_U_Socket::S_CLOSE)
					{
						pSocket->OnAlive();
						pSocket->OnSEQ(pDg);
					}
					else
					{
						FB_DELETE(pDg);
					}
					pSocket->SetUsedByIS(false);
				}
				else
				{
					FB_DELETE(pDg);
				}
			}
			break;
		case CFBNetwork_U_Dg::ACK:
			{
				CFBNetwork_U_Socket* pSocket = pU->QuerySocket(&Addr, pDg->m_Content.m_dwID, true);
				if(pSocket)
				{
					if(pSocket->m_State != CFBNetwork_U_Socket::S_CLOSE)
					{
						pSocket->OnAlive();
						pSocket->OnACK(pDg);
					}
					pSocket->SetUsedByIS(false);
				}
				FB_DELETE(pDg);
			}
			break;
		case CFBNetwork_U_Dg::WND:
			{
				CFBNetwork_U_Socket* pSocket = pU->QuerySocket(&Addr, pDg->m_Content.m_dwID, true);
				if(pSocket)
				{
					if(pSocket->m_State != CFBNetwork_U_Socket::S_CLOSE)
					{
						pSocket->OnAlive();
						pSocket->OnACK(pDg);
						pSocket->OnWnd(pDg);
					}
					pSocket->SetUsedByIS(false);
				}
				FB_DELETE(pDg);
			}
			break;
		}
	}
	return 0;
}

void CFBNetwork_U_IS::Init(CFBNetwork_U* pU)
{
	InterlockedExchange((LONG volatile*)&m_bQuit, false);

	m_pU = pU;

	DWORD dwThreadID;
	m_hThread = CreateThread(
		0,
		0, 
		(LPTHREAD_START_ROUTINE)Thread,
		this,
		0,
		&dwThreadID);
}
void CFBNetwork_U_IS::Quit(void)
{
	InterlockedExchange((volatile LONG*)&m_bQuit, true);

	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
}