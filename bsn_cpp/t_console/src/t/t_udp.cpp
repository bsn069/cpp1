#include <bsn/template_console/include/t/t.h>
#include <bsn/template_console/include/global.h>
using namespace D_N1(UDP);


T_void
t_udp_Server()
{
	wstring wstrIP;
	D_N2(Common, String)::ANSI2Unicode(g->m_strIP, wstrIP);
	T_wchar D_const * D_const pwcIP = wstrIP.c_str();
	T_uint16 D_const u16Port = g->m_u16Port;

	I_Interface* pInterface = Create();
	g->m_pLog->Write(1, pInterface->Name());
	T_int32 nRet = pInterface->Bind(pwcIP, u16Port);
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}
	T_byte byData[1024];
	size_t stLen = 0;
	wstring wstrOut;
	while (true)
	{
		pInterface->Recv(byData, 1024, stLen);
		wstrOut = str(wformat(L"Recv stLen=%1% ") % stLen);
		g->m_pLog->Write(1, wstrOut.c_str());
		pInterface->Send(byData, stLen, stLen);
		wstrOut = str(wformat(L"Send stLen=%1% ") % stLen);
		g->m_pLog->Write(1, wstrOut.c_str());
	}
	Release(pInterface);
}


T_void
t_udp_Client()
{
	wstring wstrIP;
	D_N2(Common, String)::ANSI2Unicode(g->m_strIP, wstrIP);
	T_wchar D_const * D_const pwcIP = wstrIP.c_str();
	T_uint16 D_const u16Port = g->m_u16Port;

	wstring wstrOut;
	I_Interface* pInterface = Create();
	g->m_pLog->Write(1, pInterface->Name());
	T_byte byData[1024];
	size_t stLen = 0;
	T_int32 nRet = pInterface->Bind(T_nullptr, 0);
	if (0 != nRet)
	{
		g->m_pLog->Write(1, pInterface->Error(nRet));
		return;
	}
	{
		nRet = pInterface->SetSendAddr(pwcIP, u16Port);
		if (0 != nRet)
		{
			g->m_pLog->Write(1, pInterface->Error(nRet));
			return;
		}
		wstring wstrSend(L"hello world!");
		wstrOut = str(wformat(L"%1% %2%") % wstrSend.c_str() % wstrSend.size());
		g->m_pLog->Write(1, wstrSend.c_str());
		nRet = pInterface->Send((T_byte*)wstrSend.c_str(), wstrSend.size() * 2, stLen);
		if (0 != nRet)
		{
			g->m_pLog->Write(1, pInterface->Error(nRet));
			return;
		}
		wstrOut = str(wformat(L"Send stLen=%1% ") % stLen);
		g->m_pLog->Write(1, wstrOut.c_str());

		nRet = pInterface->Recv(byData, 1000, stLen);
		if (0 != nRet)
		{
			wcout << nRet << pInterface->Error(nRet) << endl;
			return;
		}
		wstrOut = str(wformat(L"Recv stLen=%1% ") % stLen);
		g->m_pLog->Write(1, wstrOut.c_str());

		byData[stLen] = 0;
		byData[stLen+1] = 0;
		g->m_pLog->Write(1, (T_wchar*)byData);
	}
	Release(pInterface);
}