#pragma once
#include <bsn/log/include/i_interface.h>
D_BsnNamespace1(DynamicLib)
//////////////////////////////////////////////////////////////////////

class I_Interface
{
public:
	typedef D_N1(Log)::I_Interface T_Log;


protected:
	virtual ~I_Interface() {};


public:
	virtual T_wchar D_const* D_const Name() D_const = 0;
	virtual T_wchar D_const* D_const Error(T_int32 D_const i32ErrorCode) D_const = 0;

	virtual T_int32 D_const SetLog(T_Log* pLog) = 0;
	virtual T_Log* Log() = 0;

	virtual T_int32 D_const SetName(T_wchar D_const * D_const pwcLibName) = 0;
	virtual T_int32 D_const Load() = 0;
	virtual T_void* GetFunc(T_wchar D_const * D_const pwcFuncName) = 0;
	virtual T_int32 D_const Free() = 0;

	virtual wstring D_const& LibName() D_const = 0;
	virtual wstring D_const& LibFileName() D_const = 0;
	virtual T_bool D_const	 IsLoad() D_const = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


