#include "./service.h"
#include <bsn/global/include/i_service.hpp>
using namespace D_N1(Global);
D_BsnNamespace1(ServiceTCPClient)
//////////////////////////////////////////////////////////////////////

T_wchar D_const * D_const  C_Service::Name() D_const
{
	// ÎÄ¼þ¼ÐÃû
	return L"service_tcp_client";
}


T_wchar D_const * D_const C_Service::Error(T_int32 D_const i32ErrorCode) D_const
{
	if (i32ErrorCode < 0)
	{
		return I_Service::Error(i32ErrorCode);
	}

	switch (i32ErrorCode)
	{
		case 1: return L"???";
		default: return L"Unknown";
	}
}


T_int32 D_const
C_Service::Update()
{
	wstring wstrOut;
	T_int32 i32Ret;
	T_uint16 u16Port;

	T_TCPSession::T_Ptrs* pSessions = T_nullptr;
	m_pTCPClient->GetSessions(pSessions);
	for (auto& sessionPtr : *pSessions)
	{
		i32Ret = sessionPtr->GetLocalPort(u16Port);
		if (0 != i32Ret)
		{
			wstrOut = str(wformat(L"i32Ret=%1% %2%")
				% i32Ret
				% m_pGlobal->TCP()->Error(i32Ret)
				);
			D_ServiceLog(wstrOut);
			continue;;
		}

		wstrOut = str(wformat(L"new connect form port: %1%")
			% u16Port
			);
		D_ServiceLog(wstrOut);
		m_SessionPtrs.push_back(sessionPtr);
	}

	auto itor = m_SessionPtrs.begin();
	for (; itor != m_SessionPtrs.end();)
	{
		auto& sessionPtr = *itor;

		if (sessionPtr->IsClose())
		{
			i32Ret = sessionPtr->GetLocalPort(u16Port);
			if (0 != i32Ret)
			{
				wstrOut = str(wformat(L"i32Ret=%1% %2%")
					% i32Ret
					% m_pGlobal->TCP()->Error(i32Ret)
					);
				D_ServiceLog(wstrOut);
				continue;;
			}

			wstrOut = str(wformat(L"closed client port: %1%")
				% u16Port
				);
			D_ServiceLog(wstrOut);
			itor = m_SessionPtrs.erase(itor);
			continue;
		}
		++itor;
	}

	T_TCPSession::T_Buffers* pBuffers = T_nullptr;
	for (auto& sessionPtr : m_SessionPtrs)
	{
		i32Ret = sessionPtr->Recv(pBuffers);
		if (0 != i32Ret)
		{
			wstrOut = str(wformat(L"i32Ret=%1% %2%")
				% i32Ret
				% m_pGlobal->TCP()->Error(i32Ret)
				);
			D_ServiceLog(wstrOut);
			continue;
		}

		for (auto& pBuffer : *pBuffers)
		{
			wstrOut = str(wformat(L"pBuffer->Len()=%2% ")
				% pBuffer->Len()
				);
			D_ServiceLog(wstrOut);
		}
	}

	return 0;
}



C_Service::C_Service()
	: m_i32Test(0)
	, m_pTCPClient( T_nullptr )
{

}



C_Service::~C_Service()
{

}


T_int32 D_const
C_Service::Init(T_Global* pGlobal)
{
	T_int32 nRet = I_Service::Init(pGlobal);
	if (0 != nRet)
	{
		return nRet;
	}

	T_TCP* pTCP = m_pGlobal->TCP();
	nRet = pTCP->CreateClient(m_pTCPClient);
	if (0 != nRet)
	{
		return nRet;
	}

	RegCmd(L"Connect", bind(&C_Service::Cmd_Connect, this, _1));
	RegCmd(L"Send", bind(&C_Service::Cmd_Send, this, _1));
	RegCmd(L"Close", bind(&C_Service::Cmd_Close, this, _1));

	return 0;
}



T_int32 D_const
C_Service::Uninit()
{
	T_int32 nRet = I_Service::Uninit();
	if (0 != nRet)
	{
		return nRet;
	}

	for (auto& sessionPtr : m_SessionPtrs)
	{
		sessionPtr->Close();
	}
	m_SessionPtrs.clear();

	T_TCP* pTCP = m_pGlobal->TCP();
	nRet = pTCP->ReleaseClient(m_pTCPClient);
	if (0 != nRet)
	{
		return nRet;
	}

	return 0;
}


N_Bsn::T_void
C_Service::Cmd_Connect(T_Cmds D_const& Cmds)
{
	wstring wstrOut;
	if (Cmds.size() != 2)
	{
		wstrOut = str(wformat(L"%1% u16Port")
			% Cmds[0]
			);
		D_ServiceLog(wstrOut);
		return;
	}

	T_uint16 u16Port = lexical_cast<T_uint16>(Cmds[1]);
	T_int32 i32Ret = m_pTCPClient->Connect(L"127.0.0.1", u16Port, T_nullptr);
	if (0 != i32Ret)
	{
		wstrOut = str(wformat(L"i32Ret=%1% %2%")
			% i32Ret
			% m_pGlobal->TCP()->Error(i32Ret)
			);
		D_ServiceLog(wstrOut);
		return;
	}

	wstrOut = L"success";
	D_ServiceLog(wstrOut);
}


N_Bsn::T_void
C_Service::Cmd_Send(T_Cmds D_const& Cmds)
{
	wstring wstrOut;
	if (Cmds.size() != 2)
	{
		wstrOut = str(wformat(L"%1% strMsg")
			% Cmds[0]
			);
		D_ServiceLog(wstrOut);
		return;
	}

	wstring D_const& wstrMsg = Cmds[1];
	for (auto& sessionPtr : m_SessionPtrs)
	{
		sessionPtr->Send((T_byte*)wstrMsg.c_str(), wstrMsg.size() * 2);
	}

	wstrOut = L"success";
	D_ServiceLog(wstrOut);
}


N_Bsn::T_void
C_Service::Cmd_Close(T_Cmds D_const& Cmds)
{
	wstring wstrOut;
	if (Cmds.size() != 1)
	{
		wstrOut = str(wformat(L"%1%")
			% Cmds[0]
			);
		D_ServiceLog(wstrOut);
		return;
	}

	for (auto& sessionPtr : m_SessionPtrs)
	{
		sessionPtr->Close();
	}
	m_SessionPtrs.clear();

	wstrOut = L"success";
	D_ServiceLog(wstrOut);
}





D_BsnNamespace1End
