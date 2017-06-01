#include <bsn/template_console/include/t/t.h>
#include <bsn/template_console/include/global.h>
using namespace D_N1(TCP);


T_void
t_tcp_Server()
{
	wstring wstrIP;
	D_N2(Common, String)::ANSI2Unicode(g->m_strIP, wstrIP);
	T_wchar D_const * D_const pwcIP = wstrIP.c_str();
	T_uint16 D_const u16Port = g->m_u16Port;
	T_int32 nRet;

	I_Interface* pInterface = Create();
	g->m_pLog->Write(1, pInterface->Name());
	nRet = pInterface->Start();
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}
	I_Server* pServer;
	nRet = pInterface->CreateServer(pServer);
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}

	nRet = pServer->Bind(pwcIP, u16Port);
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}

	nRet = pServer->Listen();
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}

	I_Session::T_Buffers* pBuffers;
	list<I_Session::T_Ptr> Sessions;
	list<I_Session::T_Ptr>::iterator itor;
	I_Session::T_Ptrs* pSessions;
	T_byte byData[1024];
	size_t stLen = 0;
	wstring wstrOut;
	wstring wstrLocalIP;
	T_wchar D_const* pwcRemoteIP;
	T_uint16 u16RemotePort;
	T_uint16 u16LocalPort;
	while (true)
	{
		sleep_for(milliseconds(500));

		nRet = pServer->GetSessions(pSessions);
		if (0 != nRet)
		{
			g->m_pLog->Write(1, pInterface->Error(nRet));
		}

		for (I_Session::T_Ptr& session : *pSessions)
		{
			nRet = session->GetRemoteIP(pwcRemoteIP);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
				continue;
			}
			nRet = session->GetRemotePort(u16RemotePort);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
				continue;
			}
			nRet = session->GetLocalIP(wstrLocalIP);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
				continue;
			}
			nRet = session->GetLocalPort(u16LocalPort);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
				continue;
			}
			wstrOut = str(wformat(L"new connect: %3%:%4% < %1%:%2% ") 
				% pwcRemoteIP 
				% u16RemotePort
				% wstrLocalIP
				% u16LocalPort
				);
			g->m_pLog->Write(1, wstrOut.c_str());

			Sessions.push_back(session);
		}

		itor = Sessions.begin();
		for (; itor != Sessions.end(); )
		{
			I_Session::T_Ptr& session = *itor;
			nRet = session->Recv(pBuffers);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
				itor = Sessions.erase(itor);
				continue;
			}

			for (I_Buffer* pBuffer : *pBuffers)
			{
				wstrOut = str(wformat(L"pBuffer->Len()=%1% ") % pBuffer->Len());
				g->m_pLog->Write(1, wstrOut.c_str());
			}

			++itor;
		}
	}
	pInterface->ReleaseServer(pServer);
	Release(pInterface);
}


T_void
t_tcp_Client()
{
	wstring wstrIP;
	D_N2(Common, String)::ANSI2Unicode(g->m_strIP, wstrIP);
	T_wchar D_const * D_const pwcIP = wstrIP.c_str();
	T_uint16 D_const u16Port = g->m_u16Port;
	T_int32 nRet;

	I_Interface* pInterface = Create();
	g->m_pLog->Write(1, pInterface->Name());
	nRet = pInterface->Start();
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}
	I_Client* pClient;
	nRet = pInterface->CreateClient(pClient);
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}

	nRet = pClient->Connect(pwcIP, u16Port, T_nullptr);
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}

	I_Session::T_Ptr pSession;
	wstring wstrOut;

	while (!pSession)
	{
		sleep_for(milliseconds(500));

		I_Session::T_Ptrs* pSessions;
		nRet = pClient->GetSessions(pSessions);
		if (0 != nRet)
		{
			g->m_pLog->Write(1, pInterface->Error(nRet));
		}

		for (I_Session::T_Ptr& session : *pSessions)
		{
			wstring wstrLocalIP;
			T_wchar D_const* pwcRemoteIP;
			T_uint16 u16RemotePort;
			T_uint16 u16LocalPort;

			if (!session->IsConnected())
			{
				g->m_pLog->Write(1, L"!session->IsConnected()");
				nRet = pClient->Connect(pwcIP, u16Port, T_nullptr);
				if (0 != nRet)
				{
					g->m_pLog->Write(1, pInterface->Error(nRet));
				}
				break;
			}

			nRet = session->GetRemoteIP(pwcRemoteIP);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
			}
			nRet = session->GetRemotePort(u16RemotePort);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
			}
			nRet = session->GetLocalIP(wstrLocalIP);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
			}
			nRet = session->GetLocalPort(u16LocalPort);
			if (0 != nRet)
			{
				g->m_pLog->Write(1, pInterface->Error(nRet));
			}
			wstrOut = str(wformat(L"new connect: %3%:%4% > %1%:%2% ")
				% pwcRemoteIP
				% u16RemotePort
				% wstrLocalIP
				% u16LocalPort
				);
			g->m_pLog->Write(1, wstrOut.c_str());

			pSession = session;
		}
	}

	while (pSession)
	{
		sleep_for(milliseconds(500));

		if (pSession->IsClose())
		{
			g->m_pLog->Write(1, L"closed");
			pSession.reset();
			break;
		}
		
		I_Session::T_Buffers* pBuffers;
		pSession->Recv(pBuffers);
		for (I_Buffer* pBuffer : *pBuffers)
		{
			wstrOut = str(wformat(L"pBuffer->Len()=%1% ") % pBuffer->Len());
			g->m_pLog->Write(1, wstrOut.c_str());
		}

		wstring wstrSend(L"hello world!hello world!hello world!hello world!hello world!"
			L"hello world!hello world!hello world!hello world!hello world!"
			L"hello world!hello world!hello world!hello world!hello world!"
			L"hello world!hello world!hello world!hello world!hello world!"
			L"hello world!hello world!hello world!hello world!hello world!"
			);
		pSession->Send((T_byte*)wstrSend.c_str(), wstrSend.size() * 2);
		pSession->Send((T_byte*)wstrSend.c_str(), wstrSend.size() * 2);
		pSession->Close();
		pSession.reset();
	}
	pInterface->ReleaseClient(pClient);
	Release(pInterface);
}