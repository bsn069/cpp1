#include "../include/FBNetwork_Port.h"

CFBNetwork_U_Flux_Notify::CFBNetwork_U_Flux_Notify()
{
	m_hEvent = CreateEvent(0, false, false, 0);
	m_dwBytes = 0;
}
CFBNetwork_U_Flux_Notify::~CFBNetwork_U_Flux_Notify()
{
	CloseHandle(m_hEvent);
}

CFBNetwork_U_Flux::CFBNetwork_U_Flux()
{
	m_bBreak = false;

	m_dwSWnd = 65535;
	m_dwSWndNow = 0;

	m_dwRWnd = 0;
	m_dwRWndNow = 0;

	m_dwCWnd = CFBNetwork_U_Dg::TOTALSIZE * CFBNetwork_U_Socket::DELAYACKS;
	m_dwCWndSsthresh = 65535;

	m_dCWndTimerLast = 0.0;

	//m_pFile = fopen("c:\\1.txt", "w");
}
CFBNetwork_U_Flux::~CFBNetwork_U_Flux()
{
	ThreadMap::iterator it;
	for(it = m_Notifys.begin(); it != m_Notifys.end(); it++)
	{
		FB_DELETE(it->second);
	}
}

CFBNetwork_U_Flux_Notify* CFBNetwork_U_Flux::CheckIn(DWORD dwBytes, BOOL bBlock)
{
	lock_guard<mutex> Guard(m_Mutex);

	CFBNetwork_U_Flux_Notify* pNotify = 0;
	DWORD dwSize = 0;

	m_dwSWndNow += dwBytes;
	if(m_dwSWndNow > m_dwSWnd && bBlock)
	{
		dwSize = m_dwSWndNow - m_dwSWnd;

		DWORD dwThreadID = GetCurrentThreadId();
		pNotify = m_Notifys[dwThreadID];
		if(!pNotify)
		{
			pNotify = FB_NEW(CFBNetwork_U_Flux_Notify, 1);
			m_Notifys[dwThreadID] = pNotify;
		}

		pNotify->m_dwBytes = dwSize;
	}
	return pNotify;
}

BOOL CFBNetwork_U_Flux::CanFlow(DWORD dwBytes)
{
	lock_guard<mutex> Guard(m_Mutex);

	DWORD dwWnd = min(m_dwRWnd, m_dwCWnd);
	return m_dwRWndNow + dwBytes <= dwWnd;
}
BOOL CFBNetwork_U_Flux::Flow(DWORD dwBytes)
{
	lock_guard<mutex> Guard(m_Mutex);

	DWORD dwWnd = min(m_dwRWnd, m_dwCWnd);
	if(m_dwRWndNow + dwBytes <= dwWnd)
	{
		m_dwRWndNow += dwBytes;	
		return true;
	}
	return false;
}

void CFBNetwork_U_Flux::Update(DWORD dwBytes, DWORD dwRWnd)
{
	lock_guard<mutex> Guard(m_Mutex);

	m_dwSWndNow -= dwBytes;
	
	if(dwRWnd != (DWORD)(-1))
		m_dwRWnd = dwRWnd;
	m_dwRWndNow -= dwBytes;

	CFBNetwork_U_Flux_Notify* pNotify;
	ThreadMap::iterator it;
	for(it = m_Notifys.begin(); it != m_Notifys.end(); it++)
	{
		pNotify = it->second;

		if(pNotify->m_dwBytes == 0)
		{
			continue;
		}

		if(pNotify->m_dwBytes <= dwBytes)
		{
			SetEvent(pNotify->m_hEvent);

			pNotify->m_dwBytes = 0;
		}
		else
		{
			pNotify->m_dwBytes -= dwBytes;
		}
	}
}

void CFBNetwork_U_Flux::Wait(CFBNetwork_U_Flux_Notify* pNotify)
{
	while(
		pNotify &&
		!m_bBreak &&
		WaitForSingleObject(pNotify->m_hEvent, 1000) == WAIT_TIMEOUT)
	{
	}
}
void CFBNetwork_U_Flux::Break(void)
{
	InterlockedExchange((volatile LONG*)&m_bBreak, true);
}

void CFBNetwork_U_Flux::OnACK(void)
{
	lock_guard<mutex> Guard(m_Mutex);

	//double dNow = m_CWndTimer.Now();
	//if(dNow - m_dCWndTimerLast >= 1.0f)
	{
		//m_dCWndTimerLast = dNow;

		//tstring Msg;

		if(m_dwCWnd < m_dwCWndSsthresh)
		{
			m_dwCWnd += CFBNetwork_U_Dg::TOTALSIZE;

			//Msg = str(wformat(L"¬˝∆Ù∂Ø cwnd:%d ssthresh:%d rwnd:%d") % m_dwCWnd % m_dwCWndSsthresh % m_dwRWnd);

#ifdef _FILE_LOG_
			fprintf(((CFBNetwork_U*)m_pU)->m_pFile, "¬˝∆Ù∂Ø cwnd:%d ssthresh:%d\n", m_dwCWnd, m_dwCWndSsthresh);
#endif
			//fprintf(m_pFile, "¬˝∆Ù∂Ø cwnd:%d ssthresh:%d\n", m_dwCWnd, m_dwCWndSsthresh);
		}
		else
		{
			m_dwCWnd += CFBNetwork_U_Dg::TOTALSIZE * CFBNetwork_U_Dg::TOTALSIZE / m_dwCWnd;

			//Msg = str(wformat(L"”µ»˚±‹√‚ cwnd:%d ssthresh:%d rwnd:%d") % m_dwCWnd % m_dwCWndSsthresh % m_dwRWnd);

#ifdef _FILE_LOG_
			fprintf(((CFBNetwork_U*)m_pU)->m_pFile, "”µ»˚±‹√‚ cwnd:%d ssthresh:%d\n", m_dwCWnd, m_dwCWndSsthresh);
#endif
			//fprintf(m_pFile, "”µ»˚±‹√‚ cwnd:%d ssthresh:%d\n", m_dwCWnd, m_dwCWndSsthresh);
		}
		//m_Debug.Push(Msg);
	}
}
void CFBNetwork_U_Flux::OnLost(void)
{
	lock_guard<mutex> Guard(m_Mutex);

	m_dwCWndSsthresh = __max(m_dwRWndNow / 2, CFBNetwork_U_Dg::TOTALSIZE * CFBNetwork_U_Socket::DELAYACKS);
	m_dwCWnd = m_dwCWndSsthresh;

	//fprintf(m_pFile, "∂™ ß cwnd:%d ssthresh:%d\n", m_dwCWnd, m_dwCWndSsthresh);

	/*
	if(m_dwCWnd > pDg->m_dwLen)
	{
		m_dwCWnd -= pDg->m_dwLen;
	}
	m_dwCWnd = max(CFBNetwork_U_Dg::TOTALSIZE * CFBNetwork_U_Socket::DELAYACKS, m_dwCWnd);
	*/

	/*
	wstring Msg = str(wformat(L"∂™ ß(%d) cwnd:%d ssthresh:%d rwnd:%d") % pDg->m_Content.m_dwSEQ % m_dwCWnd % m_dwCWndSsthresh % m_dwRWnd);
	m_Debug.Push(Msg);
	*/
}
void CFBNetwork_U_Flux::OnTimeout(void)
{
	lock_guard<mutex> Guard(m_Mutex);

	m_dwCWndSsthresh = __max(m_dwRWndNow / 2, CFBNetwork_U_Dg::TOTALSIZE * CFBNetwork_U_Socket::DELAYACKS);
	m_dwCWnd = CFBNetwork_U_Dg::TOTALSIZE * CFBNetwork_U_Socket::DELAYACKS;

	//fprintf(m_pFile, "÷ÿ¥´ cwnd:%d ssthresh:%d --- %d\n", m_dwCWnd, m_dwCWndSsthresh, dd);

	/*
	if(m_dwCWnd > pDg->m_dwLen)
	{
		m_dwCWnd -= pDg->m_dwLen;
	}
	m_dwCWnd = max(CFBNetwork_U_Dg::TOTALSIZE * CFBNetwork_U_Socket::DELAYACKS, m_dwCWnd);
	*/

	/*
	wstring Msg = str(wformat(L"÷ÿ¥´ cwnd:%d ssthresh:%d rwnd:%d") % m_dwCWnd % m_dwCWndSsthresh % m_dwRWnd);
	m_Debug.Push(Msg);
	*/
}
