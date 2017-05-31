#pragma once
#include <bsn/tcp/include/i_interface.h>
#include "./user_tcp.h"
#include "./mgr_user.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

class C_MgrUserTCP : public C_MgrUser
{
public:
	typedef C_MgrUser	T_Base;
	typedef D_N1(TCP)::I_OnSession		T_OnSession;
	typedef unordered_map<T_uint32, T_OnSession*>		T_OnSessions;
	typedef D_N1(TCP)::I_Session::T_Ptrs	T_SessionPtrs;
	typedef D_N1(TCP)::I_Session::T_Ptr	T_SessionPtr;

	static T_int32 D_const msc_i32ErrorCodeMax = 200;
	typedef function<C_User*(T_OnSession::T_ID,T_SessionPtr&)> T_FunNewUser;

public:
	T_wchar D_const * D_const Name() D_const;
	T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const;

	T_int32 D_const AddSession(T_OnSession* pOnSession);
	T_int32 D_const DelSession(T_OnSession::T_ID ID);
	T_OnSession*	GetSession(T_OnSession::T_ID ID);

	T_void SetFunNewUser(T_FunNewUser FunNewUser){m_FunNewUser = FunNewUser;};

	virtual T_int32 D_const Update() override;

	virtual T_int32 D_const	ReleaseUser(C_User* pUser) override;

public:
	C_MgrUserTCP();
	~C_MgrUserTCP();


protected:
	T_OnSessions	m_OnSessions;
	T_FunNewUser	m_FunNewUser;

protected:
	T_int32 D_const ProcSession(T_OnSession* pOnSession);
	virtual T_int32 D_const AddUser(T_OnSession::T_ID ID, T_SessionPtr& sessionPtr);
	T_int32 D_const ProcSessions();
};



D_BsnNamespace1End
