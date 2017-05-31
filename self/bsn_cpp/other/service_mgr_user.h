#pragma once
#include "./mgr_user.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

class C_ServiceMgrUser : public I_Service
{
public:
	typedef I_Service T_Base;

public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	virtual T_int32 D_const Update() override;
	virtual T_int32 D_const Init(T_Global* pGlobal) override;
	virtual T_int32 D_const Uninit() override;


public:
	C_ServiceMgrUser();
	virtual ~C_ServiceMgrUser();

public:
	C_MgrUser* m_pMgrUser;
};


D_BsnNamespace1End
