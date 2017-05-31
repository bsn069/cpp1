#include "../include/FBNetwork_Port.h"

DWORD CFBNetwork_U_OS::Thread(CFBNetwork_U_OS* pOS)
{
	return pOS->Thread_Process();
}

DWORD CFBNetwork_U_OS::Thread_Process(void)
{
	CFBNetwork_U_OS_Notify* pNotify;
	CFBNetwork_U_Dg* pDg;

	while(1)
	{
		switch(WaitForMultipleObjects(2, m_pEvent, false, INFINITE))
		{
		case WAIT_OBJECT_0:
			{
				return 0;
			}
			break;
		case WAIT_OBJECT_0 + 1:
			{
				while(pNotify = Get())
				{
					CFBNetwork_U_Socket* pSocket = pNotify->m_pSocket;

					lock_guard<mutex> Guard(pSocket->m_SDgMutex);

					while(pDg = pSocket->m_SDgs.GetHead())
					{
						// 流量控制
						if(!pSocket->m_Flux.Flow(pDg->m_dwLen))
						{
							#ifdef _FILE_LOG_
							fprintf(m_pU->m_pFile, "没有流量\n");
							#endif
							break;
						}

						pSocket->m_SDgs.Pop(pDg);

						pDg->m_Content.m_dwSEQ = pSocket->m_dwSEQ;
						InterlockedIncrement((volatile LONG*)&pSocket->m_dwSEQ);

						lock_guard<mutex> Guard(pSocket->m_BDgMutex);

						pSocket->m_BDgs.Push_Back(pDg);
						pSocket->SendTo(pDg);

						#ifdef _FILE_LOG_
						fprintf(m_pU->m_pFile, "发送 %d\n", pDg->m_Content.m_dwSEQ);
						#endif
					}

					#ifdef _FILE_LOG_
					fprintf(m_pU->m_pFile, "没有需要发送的了\n");
					#endif

					Pop(pNotify);
				}
			}
			break;
		}
	}
	return 0;
}

void CFBNetwork_U_OS::Init(CFBNetwork_U* pU)
{
	for(DWORD n = 0; n < 2; n++)
	{
		m_pEvent[n] = CreateEvent(0, true, false, 0);
	}

	DWORD dwThreadID;
	m_hThread = CreateThread(
		0, 
		0, 
		(LPTHREAD_START_ROUTINE)Thread,
		this,
		0,
		&dwThreadID);
}
void CFBNetwork_U_OS::Quit(void)
{
	SetEvent(m_pEvent[0]);

	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);

	for(DWORD n = 0; n < 2; n++)
	{
		CloseHandle(m_pEvent[n]);
	}
}

void CFBNetwork_U_OS::Push(CFBNetwork_U_OS_Notify* pNotify)
{
	lock_guard<mutex> Guard(m_Mutex);

	BOOL bEvent = (m_Notifys.Size() == 0);
	if(!pNotify->List())
	{
		m_Notifys.Push_Back(pNotify);
	}
	if(bEvent)
	{
		SetEvent(m_pEvent[1]);
	}
}
void CFBNetwork_U_OS::Pop(CFBNetwork_U_OS_Notify* pNotify)
{
	lock_guard<mutex> Guard(m_Mutex);

	m_Notifys.Pop(pNotify);
}
CFBNetwork_U_OS_Notify* CFBNetwork_U_OS::Get(void)
{
	lock_guard<mutex> Guard(m_Mutex);

	if(m_Notifys.Size() == 0)
	{
		ResetEvent(m_pEvent[1]);
		return 0;
	}
	return m_Notifys.GetHead();
}
