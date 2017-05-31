#include <bsn/tcp/include/port.h>
#include "./service_mgr_user_tcp.h"
#include "./mgr_user_tcp.cpp"
#include "./service_mgr_user.cpp"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////


T_wchar D_const * D_const  C_ServiceMgrUserTCP::Name() D_const
{
	// ÎÄ¼þ¼ÐÃû
	return L"service_mgr_user_tcp";
}


T_wchar D_const * D_const C_ServiceMgrUserTCP::Error(T_int32 D_const i32ErrorCode) D_const
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


C_ServiceMgrUserTCP::C_ServiceMgrUserTCP()
{
	m_pMgrUser = New<D_N1(Other)::C_MgrUserTCP>();
}



C_ServiceMgrUserTCP::~C_ServiceMgrUserTCP()
{
	Delete(m_pMgrUser);
}


C_ServiceMgrUserTCP::T_TCPServer*
C_ServiceMgrUserTCP::CreateTCPServer(T_OnSession::T_ID D_const ID)
{
	T_TCPServer* pTCPServer = T_nullptr;
	T_TCP* pTCP = m_pGlobal->TCP();
	T_int32 nRet = pTCP->CreateServer(pTCPServer);
	if (0 != nRet)
	{
		 return nullptr;
	}
	pTCPServer->SetID(ID);
	((D_N1(Other)::C_MgrUserTCP*)m_pMgrUser)->AddSession(pTCPServer);
	return pTCPServer;
}


C_ServiceMgrUserTCP::T_TCPClient*
C_ServiceMgrUserTCP::CreateTCPClient(T_OnSession::T_ID D_const ID)
{
	T_TCPClient* pTCPClient = T_nullptr;
	T_TCP* pTCP = m_pGlobal->TCP();
	T_int32 nRet = pTCP->CreateClient(pTCPClient);
	if (0 != nRet)
	{
		return nullptr;
	}
	pTCPClient->SetID(ID);
	((D_N1(Other)::C_MgrUserTCP*)m_pMgrUser)->AddSession(pTCPClient);
	return pTCPClient;
}


N_Bsn::T_int32 D_const
C_ServiceMgrUserTCP::ReleaseTCPServer(T_TCPServer*& pTCPServer)
{
	T_TCP* pTCP = m_pGlobal->TCP();
	T_int32 nRet = pTCP->ReleaseServer(pTCPServer);
	if (0 != nRet)
	{
		return nRet;
	}

	return 0;
}


N_Bsn::T_int32 D_const
C_ServiceMgrUserTCP::ReleaseTCPClient(T_TCPClient*& pTCPClient)
{
	T_TCP* pTCP = m_pGlobal->TCP();
	T_int32 nRet = pTCP->ReleaseClient(pTCPClient);
	if (0 != nRet)
	{
		return nRet;
	}

	return 0;
}



D_BsnNamespace1End
