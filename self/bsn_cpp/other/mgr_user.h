#pragma once
#include "./service.h"
#include "./user.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

class C_MgrUser
{
public:
	typedef unordered_map<C_User::T_ID, C_User*>	T_ID2User;
	typedef unordered_set<C_User*>				T_Users;
	typedef list<C_User*>						T_RemoveUsers;
	typedef I_Service				T_Service;

	static T_int32 D_const msc_i32ErrorCodeMax = 100;

public:
	T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const;

	T_int32 D_const	SetService(T_Service* pService);
	T_Service*		GetService();

	T_int32 D_const	AddUser(C_User::T_ID userID, C_User* pUser);
	T_int32 D_const	DelUser(C_User::T_ID userID);
	C_User* 		GetUser(C_User::T_ID D_const userID);

	T_int32 D_const	AddUser(C_User* pUser);
	T_int32 D_const	DelUser(C_User* pUser);
	T_bool D_const	HaveUser(C_User* pUser);

	virtual T_int32 D_const Update() = 0;
	
	T_int32 D_const Init();
	T_int32 D_const Uninit();

	virtual T_int32 D_const	ReleaseUser(C_User* pUser) = 0;


public:
	C_MgrUser();
	~C_MgrUser();


protected:
	T_ID2User	m_ID2User;
	T_Users		m_Users;
	T_RemoveUsers m_RemoveUsers;
	T_Service*	m_pService;


protected:
	T_int32 D_const ProcUsers();
	T_int32 D_const ProcRemoveUsers();
};

D_BsnNamespace1End
