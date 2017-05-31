#include "./user.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////




C_User::C_User()
: m_pMsgs( T_nullptr )
, m_ID( msc_IDNull )
, m_pMgrUser( T_nullptr )
, m_pMsgParser( T_nullptr )
{
	CreateMsgParser();
}



C_User::~C_User()
{
	ReleaseMsgParser();
}



T_int32 D_const
C_User::CreateMsgParser()
{
	if (T_nullptr != m_pMsgParser)
	{
		return 2;
	}

	m_pMsgParser = D_N1(MsgParser)::Create();
	m_pMsgParser->Msgs(m_pMsgs);
	return 0;
}


T_int32 D_const
C_User::ReleaseMsgParser()
{
	if (T_nullptr == m_pMsgParser)
	{
		return 3;
	}

	m_pMsgs = nullptr;
	D_N1(MsgParser)::Release(m_pMsgParser);
	return 0;
}

T_int32 D_const
C_User::Update()
{
	T_int32 i32Ret = RecvMsg();
	if (0 == i32Ret)
	{
		i32Ret = ProcMsg();
		if (0 != i32Ret)
		{
			return 1;
		}
	}

	return i32Ret;
}


T_int32 D_const
C_User::SetMgrUser(C_MgrUser* pMgrUser)
{
	D_AssertRet(T_nullptr != pMgrUser, 1);
	D_AssertRet(T_nullptr == m_pMgrUser, 2);

	m_pMgrUser = pMgrUser;
	return 0;
}


C_MgrUser*
C_User::GetMgrUser()
{
	return m_pMgrUser;
}

D_BsnNamespace1End
