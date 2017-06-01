#pragma once
#include "./main.h"
D_BsnNamespace1(NameSpace)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

public:
	C_Interface();
	virtual ~C_Interface();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End