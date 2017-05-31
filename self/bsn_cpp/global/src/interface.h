#pragma once
#include "./main.h"
#include <bsn/other/i_global.h>
#include <bsn/other/service.h>
#include <bsn/console_input/include/i_interface.h>

using D_N1(Other)::I_Service;
using D_N1(Other)::I_Global;
D_BsnNamespace1(Global)
//////////////////////////////////////////////////////////////////////

class C_Global : public I_Global
{
public:
	typedef D_N1(ConsoleInput)::I_Interface T_ConsoleInput;
	typedef vector<T_DynamicLib*> T_DynamicLibs;

	typedef boost::program_options::options_description T_options_description;
	typedef function<T_void()> T_TestFunc;
	typedef map<string, T_TestFunc> T_TestFuncs;
	typedef vector<I_Service*> T_Services;



public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;
	
	virtual T_int32 D_const SetLog(T_Log* pLog) override;
	virtual T_Log* Log() override;
	virtual T_TCP* TCP() override;
	virtual I_Service* Service(T_uint32 D_const u32Index) override;
	virtual I_Service* Service(T_wchar D_const * D_const pwcService) override;

	virtual T_void Wmain(T_int32 argc, T_wchar* argv[]) override;


public:
	T_bool D_const Init(T_int32 argc, T_wchar* argv[]);
	T_bool D_const Uninit();

public:
	T_bool D_const	InitLog();
	T_bool D_const	UninitLog();

	T_bool D_const	InitTCP();
	T_bool D_const	UninitTCP();

	T_bool D_const	InitParam(T_int32 argc, T_wchar* argv[]);
	T_bool D_const	UnnitParam();

	T_bool D_const	InitService();
	T_bool D_const	UninitService();

	T_bool D_const	InitConsoleInput();
	T_bool D_const	UninitConsoleInput();

public:
	T_bool D_const	ServiceReg();
	T_bool D_const	ServiceLoad();
	T_bool D_const	ServiceCreate();
	T_bool D_const	ServiceInit();

	T_bool D_const	ServiceUninit();
	T_bool D_const	ServiceRelease();
	T_bool D_const	ServiceFree();

	T_bool D_const	ParamReg();

	T_void Test();


public:
	T_TCP* m_pTCP;
	T_Log* m_pLog;
	T_ConsoleInput* m_pConsoleInput;

	T_DynamicLibs	m_DynamicLibs;
	T_Services		m_Services;

	T_bool			m_bQuit;

	T_uint32	m_u32Test;
	T_TestFuncs	m_TestFuncs;
	T_options_description m_ODSystem;
	T_options_description m_ODTest;
	T_options_description m_ODTestFun;
	T_options_description m_OD;

	string		m_strIP;
	T_uint16	m_u16Port;

public:
	C_Global();
	virtual ~C_Global();
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End