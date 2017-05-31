#include "./service_echo.h"
#include "./service_mgr_user_tcp.cpp"
using D_N1(ServiceTCPServer)::C_Service;
#include "./main_service.cpp"
D_BsnNamespace1(ServiceTCPServer)
//////////////////////////////////////////////////////////////////////


T_wchar D_const * D_const  C_Service::Name() D_const
{
	// ÎÄ¼þ¼ÐÃû
	return L"service_tcp_server";
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



C_Service::C_Service()
	: m_i32Test(0)
	, m_pTCPServer( T_nullptr )
	, m_UserID(0)
{
}



C_Service::~C_Service()
{

}


T_int32 D_const
C_Service::Init(T_Global* pGlobal)
{
	T_Base::Init(pGlobal);

	((D_N1(Other)::C_MgrUserTCP*)m_pMgrUser)->SetFunNewUser(
		&C_Service::NewUser
		);
	
	m_pTCPServer = CreateTCPServer(1);

	RegCmd(L"Bind", bind(&C_Service::Cmd_Bind, this, _1));
	RegCmd(L"Listen", bind(&C_Service::Cmd_Listen, this, _1));
	RegCmd(L"StopListen", bind(&C_Service::Cmd_StopListen, this, _1));

	return 0;
}


T_int32 D_const
C_Service::Uninit()
{
	ReleaseTCPServer(m_pTCPServer);

	T_Base::Uninit(); 
	return 0;
}


N_Bsn::T_void
C_Service::Cmd_Bind(T_Cmds D_const& Cmds)
{
	wstring wstrOut;
	if (Cmds.size() != 3)
	{
		wstrOut = str(wformat(L"%1% strIP u16Port")
			% Cmds[0]
			);
		D_ServiceLog(wstrOut);
		return;
	}

	wstring D_const& wstrIP = Cmds[1];
	T_uint16 u16Port = lexical_cast<T_uint16>(Cmds[2]);
	T_int32 i32Ret = m_pTCPServer->Bind(wstrIP.c_str(), u16Port);
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
C_Service::Cmd_Listen(T_Cmds D_const& Cmds)
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

	T_int32 i32Ret = m_pTCPServer->Listen();
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
C_Service::Cmd_StopListen(T_Cmds D_const& Cmds)
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

	T_int32 i32Ret = m_pTCPServer->StopListen();
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


D_N1(Other)::C_User*
C_Service::NewUser(T_OnSession::T_ID ID, T_SessionPtr& sessionPtr)
{
	D_N1(Other)::C_UserTCPEcho* pUser = New<D_N1(Other)::C_UserTCPEcho>();
	pUser->SetSession(sessionPtr);

	return pUser;
}










D_BsnNamespace1End
