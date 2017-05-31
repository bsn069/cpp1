#pragma once
#include <bsn/tcp/include/i_interface.h>
#include "./mgr_user_tcp.h"
#include "./service_mgr_user.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

class C_ServiceMgrUserTCP : public C_ServiceMgrUser
{
public:
	typedef C_ServiceMgrUser T_Base;
	typedef D_N1(TCP)::I_Server			T_TCPServer;
	typedef D_N1(TCP)::I_Client			T_TCPClient;
	typedef C_MgrUserTCP::T_OnSession	T_OnSession;
	typedef C_MgrUserTCP::T_SessionPtr	T_SessionPtr;

public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	T_TCPServer*	CreateTCPServer(T_OnSession::T_ID D_const ID);
	T_int32 D_const	ReleaseTCPServer(T_TCPServer*& pTCPServer);
	
	T_TCPClient*	CreateTCPClient(T_OnSession::T_ID D_const ID);
	T_int32 D_const	ReleaseTCPClient(T_TCPClient*& pTCPClient);

public:
	C_ServiceMgrUserTCP();
	virtual ~C_ServiceMgrUserTCP();

public:
};


D_BsnNamespace1End
