#include "./mgr_user.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////
 


T_int32 D_const
C_MgrUser::ProcUsers()
{
	T_int32 i32Ret = 0;
	for (auto pUser : m_Users)
	{
		i32Ret = pUser->Update();
		if (i32Ret < 0)
		{
			m_RemoveUsers.push_back(pUser);
		}
	}
	return 0;
}



T_wchar D_const * D_const
C_MgrUser::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch (i32ErrorCode)
	{
		case 1: return L"session is null";
		default: return L"unknown";
	}
	static_assert(msc_i32ErrorCodeMax == 100, "do not forgot this");
}



T_int32 D_const
C_MgrUser::DelUser(C_User* pUser)
{
	D_AssertRet(nullptr != pUser, 1);
	D_AssertRet(HaveUser(pUser), 2);
	m_Users.erase(pUser);
	return 0;
}



T_bool D_const
C_MgrUser::HaveUser(C_User* pUser)
{
	D_Assert(nullptr != pUser);

	return (m_Users.find(pUser) != m_Users.end());
}



T_int32 D_const
C_MgrUser::AddUser(C_User* pUser)
{
	D_AssertRet(nullptr != pUser, 3);
	D_AssertRet(!HaveUser(pUser), 4);
	m_Users.insert(pUser);
	return 0;
}



T_int32 D_const
C_MgrUser::DelUser(C_User::T_ID userID)
{
	D_AssertRet(userID != C_User::msc_IDNull, 5);

	D_AssertRet(nullptr != GetUser(userID), 6);

	m_ID2User.erase(userID);
	return 0;
}



D_N1(Other)::C_User*
C_MgrUser::GetUser(C_User::T_ID D_const userID)
{
	auto itor = m_ID2User.find(userID);
	if (itor != m_ID2User.end())
	{
		return itor->second;
	}
	return nullptr;
}




C_MgrUser::~C_MgrUser()
{

}



C_MgrUser::C_MgrUser()
	: m_pService(T_nullptr)
{

}



T_int32 D_const
C_MgrUser::AddUser(C_User::T_ID userID, C_User* pUser)
{
	D_AssertRet(userID != C_User::msc_IDNull, 7);
	D_AssertRet(nullptr != pUser, 8);

	D_AssertRet(nullptr == GetUser(userID), 9);

	m_ID2User.insert(make_pair(userID, pUser));
	return 0;
}


T_int32 D_const
C_MgrUser::Init()
{
	return 0;
}


T_int32 D_const
C_MgrUser::Uninit()
{
	return 0;
}


C_MgrUser::T_Service*
C_MgrUser::GetService()
{
	return m_pService;
}


T_int32 D_const
C_MgrUser::SetService(T_Service* pService)
{
	m_pService = pService;
	return 0;
}





D_BsnNamespace1End
