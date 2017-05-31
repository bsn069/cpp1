#pragma once
#include <bsn/log/include/i_interface.h>
#include <bsn/tcp/include/i_interface.h>
#include <bsn/dynamic_lib/include/i_interface.h>
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////
class I_Service;
class I_Global
{
public:
	typedef D_N1(Log)::I_Interface	T_Log;
	typedef D_N1(TCP)::I_Interface	T_TCP;
	typedef D_N1(DynamicLib)::I_Interface T_DynamicLib;


protected:
	virtual ~I_Global() {};


public:
	virtual T_wchar D_const* D_const Name() D_const = 0;
	virtual T_wchar D_const* D_const Error(T_int32 D_const i32ErrorCode) D_const = 0;
	
	virtual T_int32 D_const SetLog(T_Log* pLog) = 0;
	virtual T_Log* Log() = 0;
	virtual T_TCP* TCP() = 0;
	virtual I_Service* Service(T_uint32 D_const u32Index) = 0;
	virtual I_Service* Service(T_wchar D_const * D_const pwcService) = 0;

	virtual T_void Wmain(T_int32 argc, T_wchar* argv[]) = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


