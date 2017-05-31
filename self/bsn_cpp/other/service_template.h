#pragma once
#include "./service.h"
using D_N1(Other)::I_Service;
D_BsnNamespace1(ServiceTemplate)
//////////////////////////////////////////////////////////////////////

class C_Service : public I_Service
{
public:
	typedef I_Service		T_Base;


public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	virtual T_int32 D_const Init(T_Global* pGlobal) override;
	virtual T_int32 D_const Uninit() override;
	virtual T_int32 D_const Update() override;

	T_void Cmd_Test(T_Cmds D_const& Cmds);


public:
	C_Service();
	virtual ~C_Service();

public:
};


D_BsnNamespace1End
