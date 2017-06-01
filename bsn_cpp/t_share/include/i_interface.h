#pragma once
D_BsnNamespace1(NameSpace)
//////////////////////////////////////////////////////////////////////

class I_Interface
{
public:


protected:
	virtual ~I_Interface() {};


public:
	virtual T_wchar D_const* D_const Name() D_const = 0;
	virtual T_wchar D_const* D_const Error(T_int32 D_const i32ErrorCode) D_const = 0;

};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


