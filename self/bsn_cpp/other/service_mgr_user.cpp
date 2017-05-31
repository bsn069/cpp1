#include "./service_mgr_user.h"
#include "./service.cpp"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////


T_wchar D_const * D_const  C_ServiceMgrUser::Name() D_const
{
	// ÎÄ¼þ¼ÐÃû
	return L"service_mgr_user";
}


T_wchar D_const * D_const C_ServiceMgrUser::Error(T_int32 D_const i32ErrorCode) D_const
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


T_int32 D_const
C_ServiceMgrUser::Update()
{
	m_pMgrUser->Update();

	return 0;
}



C_ServiceMgrUser::C_ServiceMgrUser()
	: m_pMgrUser( T_nullptr )
{

}



C_ServiceMgrUser::~C_ServiceMgrUser()
{

}


T_int32 D_const
C_ServiceMgrUser::Uninit()
{
	T_Base::Uninit();
	m_pMgrUser->Uninit();

	return 0;
}


T_int32 D_const
C_ServiceMgrUser::Init(T_Global* pGlobal)
{
	T_Base::Init(pGlobal);
	m_pMgrUser->SetService(this);
	m_pMgrUser->Init();
	return 0;
}



D_BsnNamespace1End
