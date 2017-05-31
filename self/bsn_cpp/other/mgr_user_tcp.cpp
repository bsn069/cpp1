#include "./mgr_user_tcp.h"
#include "./mgr_user.cpp"
#include "./user_tcp_echo.cpp"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

C_MgrUserTCP::C_MgrUserTCP()
{
}


C_MgrUserTCP::~C_MgrUserTCP()
{
}


T_wchar D_const * D_const
C_MgrUserTCP::Name() D_const
{
	return L"C_MgrUserTCP::Name";
}


T_wchar D_const * D_const
C_MgrUserTCP::Error(T_int32 D_const i32ErrorCode) D_const
{
	if (i32ErrorCode <= T_Base::msc_i32ErrorCodeMax)
	{
		return T_Base::Error(i32ErrorCode);
	}

	switch (i32ErrorCode)
	{
		case 1: return L"session is null";
		default: return L"unknown";
	}
	static_assert(msc_i32ErrorCodeMax == 200, "do not forgot this");
}


T_int32 D_const
C_MgrUserTCP::AddSession(T_OnSession* pOnSession)
{
	D_AssertRet(0 != pOnSession->GetID(), 1);
	D_AssertRet(nullptr == GetSession(pOnSession->GetID()), 2);

	m_OnSessions.insert( make_pair(pOnSession->GetID(), pOnSession) );
	return 0;
}


C_MgrUserTCP::T_OnSession*
C_MgrUserTCP::GetSession(T_OnSession::T_ID ID)
{
	D_AssertRet(0 != ID, nullptr);

	auto itor = m_OnSessions.find(ID);
	if (itor != m_OnSessions.end())
	{
		return itor->second;
	}
	return nullptr;
}


T_int32 D_const
C_MgrUserTCP::DelSession(T_OnSession::T_ID ID)
{
	D_AssertRet(0 != ID, 1);
	D_AssertRet(nullptr != GetSession(ID), 2);

	m_OnSessions.erase( ID );
	return 0;
}


T_int32 D_const
C_MgrUserTCP::ProcSessions()
{
	for (auto& i : m_OnSessions)
	{
		ProcSession(i.second);
	}
	return 0;
}


T_int32 D_const
C_MgrUserTCP::ProcSession(T_OnSession* pOnSession)
{
	D_AssertRet(nullptr != pOnSession, 1);

	T_SessionPtrs* pSessions = T_nullptr;
	pOnSession->GetSessions(pSessions);
	for (auto& sessionPtr : *pSessions)
	{
		AddUser(pOnSession->GetID(), sessionPtr);
	}

	return 0;
}



T_int32 D_const
C_MgrUserTCP::Update()
{
	ProcSessions();
	return 0;
}


T_int32 D_const
C_MgrUserTCP::ReleaseUser(C_User* pUser)
{
	D_AssertRet(T_nullptr != pUser, 1);
	Delete(pUser);
	return 0;
}



T_int32 D_const
C_MgrUserTCP::AddUser(T_OnSession::T_ID ID, T_SessionPtr& sessionPtr)
{
	D_AssertRet(sessionPtr, 1);

	C_User* pUser = m_FunNewUser(ID, sessionPtr);
	D_AssertRet(nullptr != pUser, 2);
	//D_N1(Other)::C_UserTCPEcho* pUser = New<D_N1(Other)::C_UserTCPEcho>();
	//pUser->SetSession(sessionPtr);
	T_Base::AddUser(pUser);

	return 0;
}


D_BsnNamespace1End
