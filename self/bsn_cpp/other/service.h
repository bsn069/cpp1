#pragma once
#include "./i_global.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

class I_Service
{
public:
	typedef I_Service*(*T_CreateFunc)();
	typedef T_void(*T_ReleaseFunc)(I_Service*);
	
	typedef I_Global		T_Global;
	typedef T_Global::T_Log	T_Log;
	typedef T_Global::T_TCP	T_TCP;
	typedef T_Global::T_DynamicLib T_DynamicLib;

	typedef D_N1(TCP)::I_Server		T_TCPServer;
	typedef D_N1(TCP)::I_Client		T_TCPClient;
	typedef D_N1(TCP)::I_Session	T_TCPSession;

	typedef vector<wstring>	T_Cmds;
	typedef function<T_void(T_Cmds D_const&)> T_CmdFunc;
	typedef map<wstring, T_CmdFunc> T_CmdFuncs;


public:
	virtual T_wchar D_const * D_const Name() D_const = 0;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const;

	virtual T_int32 D_const Init(T_Global* pGlobal);
	virtual T_int32 D_const Cmd(wstring D_const& wstrCmd, T_Cmds D_const& Cmds);
	virtual T_int32 D_const Update() = 0;
	virtual T_int32 D_const Uninit();

	virtual T_bool D_const IsInit() D_const;
	virtual T_bool D_const IsUninit() D_const;


protected:
	I_Service();
	virtual ~I_Service();


protected:
	T_Global*	m_pGlobal;
	T_CmdFuncs	m_CmdFuncs;
	
	T_bool m_bInit;
	T_bool m_bUninit;


protected:
	T_void RegCmd(wstring D_const& wstrCmd, T_CmdFunc cmdFunc);
};



#define  D_ServiceLog(wstrOut) \
D_Log(m_pGlobal->Log(), wstrOut.c_str())










//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


