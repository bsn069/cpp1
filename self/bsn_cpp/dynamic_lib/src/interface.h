#pragma once
#include "./main.h"
D_BsnNamespace1(DynamicLib)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;
	
	virtual T_int32 D_const SetLog(T_Log* pLog) override;
	virtual T_Log* Log() override;

	virtual T_int32 D_const SetName(T_wchar D_const * D_const pwcLibName) override;
	virtual T_int32 D_const Load() override;
	virtual T_void* GetFunc(T_wchar D_const * D_const pwcFuncName) override;
	virtual T_int32 D_const Free() override;

	virtual wstring D_const& LibName() D_const override;
	virtual wstring D_const& LibFileName() D_const override;
	virtual T_bool D_const	 IsLoad() D_const override;


public:
	HMODULE 	m_Lib;
	wstring		m_wstrName;
	wstring		m_wstrLibName;
	T_Log*		m_pLog;

public:
	C_Interface();
	virtual ~C_Interface();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End