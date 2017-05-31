#pragma once

#include "./main.h"

D_BsnNamespace1(ServiceTCPClient)
//////////////////////////////////////////////////////////////////////

class C_Service : public D_N1(Global)::I_Service
{
public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	virtual T_int32 D_const Update() override;
	virtual T_int32 D_const Init(T_Global* pGlobal) override;
	virtual T_int32 D_const Uninit() override;

	T_void Cmd_Connect(T_Cmds D_const& Cmds);
	T_void Cmd_Send(T_Cmds D_const& Cmds);
	T_void Cmd_Close(T_Cmds D_const& Cmds);

public:
	C_Service();
	virtual ~C_Service();

public:
	T_int32 m_i32Test;
	T_TCPClient* m_pTCPClient;
	T_TCPSession::T_Ptrs m_SessionPtrs;
};


D_BsnNamespace1End
