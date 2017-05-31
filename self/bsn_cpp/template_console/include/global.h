#pragma once

#include <bsn/template_console/include/main.h>


class C_Global
{
public:
	typedef boost::program_options::options_description T_options_description;
	typedef function<T_void()> T_TestFunc;
	typedef map<string, T_TestFunc> T_TestFuncs;


public:
	T_void Run(T_int32 argc, T_wchar* argv[]);


public:
	T_uint32	m_u32Test;
	T_TestFuncs	m_TestFuncs;
	T_options_description m_ODSystem;
	T_options_description m_ODTest;
	T_options_description m_ODTestFun;
	T_options_description m_OD;

	D_N1(Log)::I_Interface* m_pLog;

	string		m_strIP;
	T_uint16	m_u16Port;


public:
	C_Global();


private:
	T_bool D_const Init(T_int32 argc, T_wchar* argv[]);
	T_bool D_const InitParam();
	T_bool D_const ProcParam(T_int32 argc, T_wchar* argv[]);
	T_bool D_const Release();
};
extern C_Global* g;

