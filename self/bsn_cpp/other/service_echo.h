#pragma once
#include "./service_mgr_user_tcp.h"
using D_N1(Other)::C_ServiceMgrUserTCP;
using D_N1(Other)::C_User;
D_BsnNamespace1(ServiceTCPServer)
//////////////////////////////////////////////////////////////////////

class C_Service : public C_ServiceMgrUserTCP
{
public:
	typedef C_ServiceMgrUserTCP		T_Base;
	typedef T_Base::T_OnSession		T_OnSession;
	typedef T_Base::T_SessionPtr	T_SessionPtr;


public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	virtual T_int32 D_const Init(T_Global* pGlobal) override;
	virtual T_int32 D_const Uninit() override;

	T_void Cmd_Bind(T_Cmds D_const& Cmds);
	T_void Cmd_Listen(T_Cmds D_const& Cmds);
	T_void Cmd_StopListen(T_Cmds D_const& Cmds);

	static C_User* NewUser(T_OnSession::T_ID ID, T_SessionPtr& sessionPtr);

public:
	C_Service();
	virtual ~C_Service();

public:
	C_User::T_ID m_UserID;
	T_int32 m_i32Test;
	T_TCPServer* m_pTCPServer;
};


D_BsnNamespace1End
